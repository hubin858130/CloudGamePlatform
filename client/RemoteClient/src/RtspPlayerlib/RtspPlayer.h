#pragma once

#include "resource.h"
#include "ourRTSPClient.h"
#include "StaticData.h"


//调用入口：
int doWinMain(HWND hWnd, char* szUrl, int nWidht, int nHight, OnPlayerStatusCallBack callback);
int closeDoMain();

// 响应SmartPlayer发送来的开始消息
bool OnMessageStart(WPARAM wParam, LPARAM lParam);

// 发送消息到SmartPlayer
bool SendMessageToSmartPlayer(HWND hWnd, MSG msg);


// 此为一个Sink类,完成对通过RTSP协议,接收并处理视频流数据

class DummySink: public MediaSink {
public:
  static DummySink* createNew(UsageEnvironment& env,
			      MediaSubsession& subsession, // identifies the kind of data that's being received
			      char const* streamId = NULL); // identifies the stream itself (optional)

private:
  DummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId);
    // called only by "createNew()"
  virtual ~DummySink();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
								struct timeval presentationTime,
                                unsigned durationInMicroseconds);

  void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

private:
  // redefined virtual functions:
  virtual Boolean continuePlaying();

private:
  u_int8_t* fReceiveBuffer;
  MediaSubsession& fSubsession;
  char* fStreamId;
  int   ID;
  FILE* fp;
};


// ffmpeg的初始化函数
bool ffmpeg_init();

// PacketQueue初始化
void packet_queue_init(PacketQueue *q);

// 存入PacketQueue数据
int packet_queue_put(PacketQueue *q, AVPacket *pkt);

// 将PacketQueue置空
void packet_queue_flush(PacketQueue *q);

// 销毁PacketQueue
void packet_queue_destroy(PacketQueue *q);

static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);

// SDL播放线程函数
int play_thread(LPVOID lpParam);

// Forward function definitions:
// RTSP 'response handlers':
void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString);
void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString);
void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString);

// Other event handler functions:
void subsessionAfterPlaying(void* clientData); // called when a stream's subsession (e.g., audio or video substream) ends
void subsessionByeHandler(void* clientData); // called when a RTCP "BYE" is received for a subsession
void streamTimerHandler(void* clientData);
  // called at the end of a stream's expected duration (if the stream has not already signaled its end using a RTCP "BYE")

// The main streaming routine (for each "rtsp://" URL):
void openURL(UsageEnvironment& env, char const* progName, char const* rtspURL);

// Used to iterate through each stream's 'subsessions', setting up each one:
void setupNextSubsession(RTSPClient* rtspClient);

// Used to shut down and close a stream (including its "RTSPClient" object):
void shutdownStream(RTSPClient* rtspClient, int exitCode = 1);

// A function that outputs a string that identifies each stream (for debugging output).  Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const RTSPClient& rtspClient);

// A function that outputs a string that identifies each subsession (for debugging output).  Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const MediaSubsession& subsession);

void usage(UsageEnvironment& env, char const* progName);

// 清楚一些全局变量,为下次播放做准备
void ClearPlayerResoure();