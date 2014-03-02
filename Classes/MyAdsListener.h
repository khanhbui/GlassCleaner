/*
 * MyAdsListener.h
 *
 *  Created on: Mar 2, 2014
 *      Author: u1198
 */

#ifndef MYADSLISTENER_H_
#define MYADSLISTENER_H_

#include "ProtocolAds.h"
#include "PluginManager.h"

class MyAdsListener : public cocos2d::plugin::AdsListener {
  //Ads
  virtual void onAdsResult(cocos2d::plugin::AdsResultCode code, const char* msg) {}
  virtual void onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points) {}
};
#endif /* MYADSLISTENER_H_ */
