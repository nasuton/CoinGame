#include "ManagingSound.h"
#include "FindLength.h"
#include "JsonHelper.h"

#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace experimental;

ManagingSound* ManagingSound::instance = nullptr;
Scheduler* ManagingSound::managerScheduler = nullptr;

ManagingSound::ManagingSound()
	:bgmId(-1)
	,bgmFileName("")
	,bgmFileExt("")
	,bgmVolume(0.5f)
	,seVolume(0.5f)
	,fadeCondition(FadeType::NONE)
	,fadeVolumeFrom(0.0f)
	,fadeVolumeTo(0.0f)
	,fadeVolumeNow(0.0f)
	,fadeTime(0.0f)
	,stopBgmReleaseFlg(true)
{
	for (int i = 0; i < FindLength::ArrayLength(seChunk); i++)
	{
		seChunk[i] = AudioEngine::INVALID_AUDIO_ID;
	}
}

ManagingSound::~ManagingSound()
{
	CC_SAFE_RELEASE_NULL(managerScheduler);
}

ManagingSound* ManagingSound::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ManagingSound();

		managerScheduler = Director::getInstance()->getScheduler();
		managerScheduler->retain();
		managerScheduler->scheduleUpdate(instance, 0, false);
	}

	return instance;
}

void ManagingSound::DeleteInstance()
{
	if (instance != nullptr)
	{
		delete instance;
	}

	instance = nullptr;
}

void ManagingSound::update(float delta)
{
	switch (fadeCondition)
	{
	case FadeType::FADE_IN:
	case FadeType::FADE_IN_RESUME:
		if (fadeTime == 0.0f)
		{
			fadeTime = 0.1f;
		}

		fadeVolumeNow += (delta * (fadeVolumeTo - fadeVolumeFrom)) / fadeTime;

		if (fadeVolumeTo <= fadeVolumeNow)
		{
			fadeVolumeNow = fadeVolumeTo;
			fadeVolumeFrom = fadeVolumeTo;
			fadeCondition = FadeType::NONE;
		}
		this->SetBgmVolume(fadeVolumeNow, false);
		break;

	case FadeType::FADE_OUT:
	case FadeType::FADE_OUT_PAUSE:
		if (fadeTime == 0.0)
		{
			fadeTime = 0.01f;
		}

		fadeVolumeNow += (delta * (fadeVolumeTo - fadeVolumeFrom)) / fadeTime;

		if (fadeVolumeNow <= fadeVolumeTo)
		{
			fadeVolumeNow = fadeVolumeTo;
			fadeVolumeFrom = fadeVolumeTo;

			if (fadeCondition == FadeType::FADE_OUT)
			{
				this->StopBgm(0.0f, stopBgmReleaseFlg);
			}
			else if(fadeCondition == FadeType::FADE_OUT_PAUSE)
			{
				this->PauseBgm(0.0f);
			}
			fadeCondition = FadeType::NONE;
		}

		this->SetBgmVolume(fadeVolumeNow, false);
		break;

	default:
		break;
	}
}

bool ManagingSound::ReadAudioFile(std::string jsonName)
{
	rapidjson::Document audioDoc = JsonHelper::DocumentParse<rapidjson::kParseDefaultFlags>(jsonName);

	if (audioDoc.HasParseError())
	{
		log("json parse error %s.", jsonName.c_str());

		return false;
	}

	if (audioDoc.IsObject())
	{
		bgmList.clear();
		seList.clear();

		const rapidjson::Value& listBgm = audioDoc["BGM"];
		for (rapidjson::Value::ConstMemberIterator itr = listBgm.MemberBegin(); itr != listBgm.MemberEnd(); itr++)
		{
			std::string key = itr->name.GetString();
			const rapidjson::Value& value = itr->value;
			if (value.GetType() == rapidjson::kStringType)
			{
				bgmList[key] = value.GetString();
			}
		}

		const rapidjson::Value& listSe = audioDoc["SE"];
		for (rapidjson::Value::ConstMemberIterator itr = listSe.MemberBegin(); itr != listSe.MemberEnd(); itr++)
		{
			std::string key = itr->name.GetString();
			const rapidjson::Value& value = itr->value;
			if (value.GetType() == rapidjson::kStringType)
			{
				seList[key] = value.GetString();
			}
		}

		audioListFile = jsonName;
		return true;
	}

	return false;
}

void ManagingSound::ReleaseAll()
{
	AudioEngine::uncacheAll();
}

void ManagingSound::InitVolume(float bgm, float se)
{
	bgmVolume = bgm;

	seVolume = se;
}

void ManagingSound::EndAudioEngine()
{
	AudioEngine::end();
}

int ManagingSound::PlayBgm(std::string bgmName, float fade, bool loop)
{
	return this->PlayBgm(bgmName, fade, loop, bgmVolume);
}

int ManagingSound::PlayBgm(std::string bgmName, float fade, bool loop, float volume)
{
	int soundId = AudioEngine::INVALID_AUDIO_ID;

	std::string fileName = this->GetExtension(AudioType::BGM, bgmName);

	if (fileName == "")
	{
		return soundId;
	}

	if (bgmFileName == bgmName && AudioEngine::getState(bgmId) == AudioEngine::AudioState::PLAYING)
	{
		return bgmId;
	}

	bgmFileExt = fileName.substr(fileName.size() - 4, 4);

	this->StopBgm();

	if (fade != 0.0f)
	{
		fadeCondition = FadeType::FADE_IN;
		fadeVolumeNow = 0.0f;
		fadeVolumeFrom = 0.0f;
		fadeTime = fade;
	}
	else
	{
		fadeCondition = FadeType::NONE;
		fadeVolumeNow = volume;
	}

	fadeVolumeTo = volume;

	bgmId = AudioEngine::play2d(fileName, loop, volume);

	if (loop)
	{
		AudioEngine::setFinishCallback(bgmId,
			[this, loop, volume](int audioId, std::string file) {
			this->StopBgm(0.0f, false);
			bgmId = PlayBgm(bgmFileName, 0.0f, loop, volume);
		});
	}

	bgmFileName = bgmName;

	return bgmId;
}

void ManagingSound::PauseBgm(float fade)
{
	fadeVolumeTo = 0.0f;
	if (fade != 0.0f)
	{
		fadeCondition = FadeType::FADE_OUT_PAUSE;
		fadeVolumeNow = bgmVolume;
		fadeVolumeFrom = bgmVolume;
		fadeTime = fade;
	}
	else
	{
		fadeCondition = FadeType::NONE;
		fadeVolumeNow = 0.0f;

		this->PauseBgmEngine();
	}
}

void ManagingSound::StopBgm(float fade, bool release)
{
	fadeVolumeTo = 0.0f;

	if (fade != 0.0f)
	{
		fadeCondition = FadeType::FADE_OUT;
		fadeVolumeNow = bgmVolume;
		fadeVolumeFrom = bgmVolume;
		fadeTime = fade;
		stopBgmReleaseFlg = release;
	}
	else
	{
		fadeCondition = FadeType::NONE;
		fadeVolumeNow = 0.0f;
		this->StopBgmEngine(release);
	}
}

bool ManagingSound::IsPlayingBgm()
{
	if (bgmFileName == "")
	{
		return false;
	}

	std::string fileName = bgmFileName + bgmFileExt;

	AudioEngine::AudioState state = AudioEngine::getState(bgmId);
	if (state == AudioEngine::AudioState::PLAYING)
	{
		return true;
	}

	return false;
}

void ManagingSound::SetBgmVolume(float volume, bool save)
{
	if (save)
	{
		bgmVolume = volume;
	}

	AudioEngine::setVolume(bgmId, volume);
}

float ManagingSound::GetBgmVolume()
{
	return bgmVolume;
}

void ManagingSound::ReleaseBgm()
{
	auto fileName = bgmFileName + bgmFileExt;
	AudioEngine::uncache(fileName);
}

int ManagingSound::PlaySe(std::string seName, int chunkNumber)
{
	return this->PlaySe(seName, chunkNumber, false, seVolume);
}

int ManagingSound::PlaySe(std::string seName, int chunkNumber, bool loop, float volume)
{
	int soundId = AudioEngine::INVALID_AUDIO_ID;

	bool chunkFlag = false;

	std::string fileName = GetExtension(AudioType::SE, seName);

	if (fileName == "")
	{
		return soundId;
	}

	if (0 <= chunkNumber && chunkNumber < FindLength::ArrayLength(seChunk))
	{
		chunkFlag = true;

		this->StopSe(seChunk[chunkNumber]);
	}

	soundId = AudioEngine::play2d(seName, loop, volume);

	if (chunkFlag)
	{
		seChunk[chunkNumber] = soundId;
	}

	return soundId;
}

int ManagingSound::PlaySe(std::string seName, bool loop)
{
	return this->PlaySe(seName, loop, seVolume);
}

int ManagingSound::PlaySe(std::string seName, bool loop, float volume)
{
	return this->PlaySe(seName, -1, loop, volume);
}

void ManagingSound::StopSe(int seId)
{
	AudioEngine::stop(seId);
}

void ManagingSound::SetSeVolume(float volume)
{
	seVolume = volume;
}

float ManagingSound::GetSeVolume()
{
	return seVolume;
}

void ManagingSound::ReleaseSe(std::string seName)
{
	std::string fileName = GetExtension(AudioType::SE, seName);

	if (fileName == "")
	{
		return;
	}

	AudioEngine::uncache(fileName);
}

std::string ManagingSound::GetExtension(ManagingSound::AudioType type, std::string audioName)
{
	std::string extension = ".m4a";

	if (audioListFile != "")
	{
		if (type == AudioType::BGM)
		{
			if (bgmList.count(audioName) != 0)
			{
				audioName = bgmList[audioName];
			}
		}
		else if (type == AudioType::SE)
		{
			if (seList.count(audioName) != 0)
			{
				audioName = seList[audioName];
			}
		}
	}

	if (audioName.find_last_of(".") != std::string::npos)
	{
		if (FileUtils::getInstance()->isFileExist(audioName))
		{
			return audioName;
		}
		else
		{
			return "";
		}
	}

	if (FileUtils::getInstance()->isFileExist(audioName + extension))
	{
		return audioName + extension;
	}

	log("file not found %s.", audioName.c_str());
	return audioName;
}

void ManagingSound::PauseBgmEngine()
{
	AudioEngine::pause(bgmId);
}

void ManagingSound::StopBgmEngine(bool release)
{
	AudioEngine::stop(bgmId);

	if (release)
	{
		this->ReleaseBgm();
	}

	bgmId = AudioEngine::INVALID_AUDIO_ID;
	bgmFileName = "";
	bgmFileExt = "";
}