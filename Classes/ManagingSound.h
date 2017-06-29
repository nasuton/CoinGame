#ifndef ManagingSound_h
#define ManagingSound_h

#include "cocos2d.h"

class ManagingSound
{
private:
	enum AudioType
	{
		BGM = 0,
		SE,
	};

	enum FadeType
	{
		NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_IN_RESUME,
		FADE_OUT_PAUSE,
	};

	static ManagingSound* instance;

	static cocos2d::Scheduler* managerScheduler;

	std::map<std::string, std::string> bgmList;

	std::map<std::string, std::string> seList;

	int seChunk[4];

	int bgmId;

	std::string bgmFileName;

	std::string bgmFileExt;

	CC_SYNTHESIZE(std::string, audioListFile, AudioListFile);

	//����
	float bgmVolume;
	float seVolume;

	//BGM�t�F�[�h�֘A
	FadeType fadeCondition;
	float fadeVolumeFrom;
	float fadeVolumeTo;
	float fadeVolumeNow;
	float fadeTime;
	bool stopBgmReleaseFlg;

public:
	~ManagingSound();

	static ManagingSound* GetInstance();

	static void DeleteInstance();

	virtual void update(float delta);

	//�Ǘ��t�@�C����ǂݍ���
	bool ReadAudioFile(std::string jsonName);

	void ReleaseAll();

	//���ʂ̏�����
	void InitVolume(float bgm, float se);

	//AudioEngine���
	void EndAudioEngine();

	//---------------------------------------BGM---------------------------------------//
	//BGM�Đ�
	int PlayBgm(std::string bgmName, float fade = 0.0f, bool loop = true);
	int PlayBgm(std::string bgmName, float fade, bool loop, float volume);

	//BGM�ꎞ��~
	void PauseBgm(float fade = 0.0f);

	//BGM��~
	void StopBgm(float fade = 0.0f, bool release = true);

	//BGM�Đ������ǂ���
	bool IsPlayingBgm();

	//BGM���ʕύX
	void SetBgmVolume(float volume, bool save = true);

	//BGM���ʎ擾
	float GetBgmVolume();

	//BGM�L���b�V�����
	void ReleaseBgm();

	//---------------------------------------SE---------------------------------------//
	//SE�Đ�
	int PlaySe(std::string seName, int chunkNumber);
	int PlaySe(std::string seName, int chunkNumber, bool loop, float volume);
	int PlaySe(std::string seName, bool loop = false);
	int PlaySe(std::string seName, bool loop, float volume);

	//SE��~
	void StopSe(int seId);

	//SE���ʕύX
	void SetSeVolume(float volume);

	//SE���ʎ擾
	float GetSeVolume();

	//SE�L���b�V�����
	void ReleaseSe(std::string seName);

private:
	ManagingSound();

	//�g���q�̎擾
	std::string GetExtension(AudioType type, std::string audioName);

	//pauseBGM�̎��s
	void PauseBgmEngine();
	
	//stopBGM�̎��s
	void StopBgmEngine(bool release = true);
};

#endif