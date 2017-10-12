#ifndef ManagingSound_h
#define ManagingSound_h

#include "cocos2d.h"

class ManagingSound
{
private:
	//bgmかseか
	enum AudioType
	{
		BGM = 0,
		SE,
	};

	//fadeのタイプ
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

	//jsonをしようする場合使用
	std::map<std::string, std::string> bgmList;

	//josnを使用する場合使用する
	std::map<std::string, std::string> seList;

	//4つまでSEを使用できる
	int seChunk[4];

	//BGM
	int bgmId;

	//同じものかどうか判断するため
	std::string bgmFileName;

	//拡張子
	std::string bgmFileExt;

	CC_SYNTHESIZE(std::string, audioListFile, AudioListFile);

	//音量
	float bgmVolume;
	float seVolume;

	//BGMフェード関連
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

	//管理ファイルを読み込む
	bool ReadAudioFile(std::string jsonName);

	void ReleaseAll();

	//音量の初期化
	void InitVolume(float bgm, float se);

	//AudioEngine解放
	void EndAudioEngine();

	//---------------------------------------BGM---------------------------------------//
	//BGM再生
	int PlayBgm(std::string bgmName, float fade = 0.0f, bool loop = true);
	int PlayBgm(std::string bgmName, float fade, bool loop, float volume);

	//BGM一時停止
	void PauseBgm(float fade = 0.0f);

	//BGM停止
	void StopBgm(float fade = 0.0f, bool release = true);

	//BGM再生中かどうか
	bool IsPlayingBgm();

	//BGM音量変更
	void SetBgmVolume(float volume, bool save = true);

	//BGM音量取得
	float GetBgmVolume();

	//BGMキャッシュ解放
	void ReleaseBgm();

	//---------------------------------------SE---------------------------------------//
	//SE再生
	int PlaySe(std::string seName, int chunkNumber);
	int PlaySe(std::string seName, int chunkNumber, bool loop, float volume);
	int PlaySe(std::string seName, bool loop = false);
	int PlaySe(std::string seName, bool loop, float volume);

	//SE停止
	void StopSe(int seId);

	//SE音量変更
	void SetSeVolume(float volume);

	//SE音量取得
	float GetSeVolume();

	//SEキャッシュ解放
	void ReleaseSe(std::string seName);

private:
	ManagingSound();

	//拡張子の取得
	std::string GetExtension(AudioType type, std::string audioName);

	//pauseBGMの実行
	void PauseBgmEngine();
	
	//stopBGMの実行
	void StopBgmEngine(bool release = true);
};

#endif