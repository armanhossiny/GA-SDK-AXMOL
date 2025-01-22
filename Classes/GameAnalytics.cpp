#include <sstream>
#include <ostream>
#include "axmol.h"
#include "Native/GameAnalytics.h"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
#include "Native/android/GameAnalyticsCpp.h"
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include "GameAnalyticsJNI.h"
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#include "Native/win32/GameAnalytics.h"
#endif
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#define GA_VERSION "axmol 4.1.7"

namespace gameanalytics {
    namespace axmol
    {
        bool GameAnalytics::isWritablePathSet = false;

        void addValueToJSON(const std::string &key, const ::ax::Value &value, rapidjson::Document &d, rapidjson::Document::AllocatorType &allocator)
        {
            rapidjson::Value jsonValue;
            if (!value.isNull())
            {
                const ::ax::Value::Type type = value.getType();
                if (type == ::ax::Value::Type::VECTOR)
                {
                    rapidjson::Document documentArray;
                    documentArray.SetArray();

                    for (const ::ax::Value &vectorValue : value.asValueVector())
                    {
                        addValueToJSON("", vectorValue, documentArray, allocator);
                    }

                    jsonValue = documentArray.Move();
                }
                else if (type == ::ax::Value::Type::MAP)
                {
                    rapidjson::Document documentObject;
                    documentObject.SetObject();

                    for (const std::pair<std::string, ::ax::Value> &pair : value.asValueMap())
                    {
                        addValueToJSON(pair.first, pair.second, documentObject, allocator);
                    }

                    jsonValue = documentObject.Move();
                }
                else
                {
                    switch (type)
                    {
                        /*case ::ax::Value::Type::BYTE:
                            jsonValue = value.asByte();
                            break;*/
                        case ::ax::Value::Type::INTEGER:
                            jsonValue = value.asInt();
                            break;
                            /* case ::ax::Value::Type::UNSIGNED:
                                 jsonValue = value.asUnsignedInt();
                                 break;*/
                        case ::ax::Value::Type::FLOAT:
                            jsonValue = value.asFloat();
                            break;
                        case ::ax::Value::Type::DOUBLE:
                            jsonValue = value.asDouble();
                            break;
                        case ::ax::Value::Type::BOOLEAN:
                            jsonValue = value.asBool();
                            break;
                        case ::ax::Value::Type::STRING:
                            jsonValue = rapidjson::Value(value.asString().c_str(), allocator);
                            break;
                        default:
                            //CCASSERT(false, "Value type not supported");
                            break;
                    }
                }
            }

            if (key.empty())
            {
                d.PushBack(jsonValue, allocator);
            }
            else
            {
                d.AddMember(rapidjson::Value(key.c_str(), allocator), jsonValue, allocator);
            }
        }

        std::string getStringFromValueMap(const ::ax::ValueMap &map)
        {
            rapidjson::Document d;
            d.SetObject();

            for (const std::pair<std::string, ::ax::Value> &pair : map)
            {
                addValueToJSON(pair.first, pair.second, d, d.GetAllocator());
            }

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            d.Accept(writer);

            return buffer.GetString();
        }

        void GameAnalytics::configureAvailableCustomDimensions01(const std::vector<std::string>& list)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureAvailableCustomDimensions01(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureAvailableCustomDimensions01(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureAvailableCustomDimensions01(list);
#endif
        }

        void GameAnalytics::configureAvailableCustomDimensions02(const std::vector<std::string>& list)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureAvailableCustomDimensions02(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureAvailableCustomDimensions02(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureAvailableCustomDimensions02(list);
#endif
        }

        void GameAnalytics::configureAvailableCustomDimensions03(const std::vector<std::string>& list)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureAvailableCustomDimensions03(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureAvailableCustomDimensions03(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureAvailableCustomDimensions03(list);
#endif
        }

        void GameAnalytics::configureAvailableResourceCurrencies(const std::vector<std::string>& list)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureAvailableResourceCurrencies(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureAvailableResourceCurrencies(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureAvailableResourceCurrencies(list);
#endif
        }

        void GameAnalytics::configureAvailableResourceItemTypes(const std::vector<std::string>& list)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureAvailableResourceItemTypes(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureAvailableResourceItemTypes(list);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureAvailableResourceItemTypes(list);
#endif
        }

        void GameAnalytics::configureBuild(const char *build)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureBuild(build);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureBuild(build);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureBuild(build);
#endif
        }

        void GameAnalytics::configureAutoDetectAppVersion(bool flag)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureAutoDetectAppVersion(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureAutoDetectAppVersion(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::configureUserId(const char *userId)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureUserId(userId);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureUserId(userId);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureUserId(userId);
#endif
        }

        void GameAnalytics::configureSdkGameEngineVersion(const char *gameEngineSdkVersion)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureSdkGameEngineVersion(gameEngineSdkVersion);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureSdkGameEngineVersion(gameEngineSdkVersion);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureSdkGameEngineVersion(gameEngineSdkVersion);
#endif
        }

        void GameAnalytics::configureGameEngineVersion(const char *gameEngineVersion)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::configureGameEngineVersion(gameEngineVersion);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_configureGameEngineVersion(gameEngineVersion);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::configureGameEngineVersion(gameEngineVersion);
#endif
        }

        void GameAnalytics::initialize(const char *gameKey, const char *gameSecret)
        {
            lazySetWritablePath();
            configureSdkGameEngineVersion(GA_VERSION);

            int v = AX_VERSION_NUM;
            int hi = (v & 0x00FF0000) >> 16;
            int me = (v & 0x0000FF00) >> 8;
            int lo = v & 0x000000FF;
            std::stringstream stream;
            stream << "axmol " << std::hex << hi << "." << std::hex << me << "." << std::hex << lo;
            configureGameEngineVersion(stream.str().c_str());

#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::initialize(gameKey, gameSecret);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_initialize(gameKey, gameSecret);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::initialize(gameKey, gameSecret);
#endif
        }

#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt)
        {
            GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, "", false);
        }

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const ::ax::ValueMap &fields)
        {
            addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, fields, false);
        }

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const ::ax::ValueMap &fields, bool mergeFields)
        {
            GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, getStringFromValueMap(fields).c_str(), mergeFields);
        }

        void GameAnalytics::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType)
        {
            GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(currency, amount, itemType, itemId, cartType, "", false);
        }

        void GameAnalytics::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const ::ax::ValueMap &fields)
        {
            addBusinessEventAndAutoFetchReceipt(currency, amount, itemType, itemId, cartType, fields, false);
        }

        void GameAnalytics::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const ::ax::ValueMap &fields, bool mergeFields)
        {
            GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(currency, amount, itemType, itemId, cartType, getStringFromValueMap(fields).c_str(), mergeFields);
        }
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature)
        {
            jni_addBusinessEventWithReceipt(currency, amount, itemType, itemId, cartType, receipt, "google_play", signature, "", false);
        }

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature, const ::ax::ValueMap &fields)
        {
            addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, signature, fields, false);
        }

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature, const ::ax::ValueMap &fields, bool mergeFields)
        {
            jni_addBusinessEventWithReceipt(currency, amount, itemType, itemId, cartType, receipt, "google_play", signature, getStringFromValueMap(fields).c_str(), mergeFields);
        }
#endif

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, "", "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addBusinessEvent(currency, amount, itemType, itemId, cartType, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType, "", false);
#endif
        }

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const ::ax::ValueMap &fields)
        {
            addBusinessEvent(currency, amount, itemType, itemId, cartType, fields, false);
        }

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, "", getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addBusinessEvent(currency, amount, itemType, itemId, cartType, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addResourceEvent((int)flowType, currency, amount, itemType, itemId, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addResourceEvent((int)flowType, currency, amount, itemType, itemId, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addResourceEvent((gameanalytics::EGAResourceFlowType)((int)flowType), currency, amount, itemType, itemId, "", false);
#endif
        }

        void GameAnalytics::addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId, const ::ax::ValueMap &fields)
        {
            addResourceEvent(flowType, currency, amount, itemType, itemId, fields, false);
        }

        void GameAnalytics::addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addResourceEvent((int)flowType, currency, amount, itemType, itemId, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addResourceEvent((int)flowType, currency, amount, itemType, itemId, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addResourceEvent((gameanalytics::EGAResourceFlowType)((int)flowType), currency, amount, itemType, itemId, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01)
        {
            addProgressionEvent(progressionStatus, progression01, "", "");
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const ::ax::ValueMap &fields)
        {
            addProgressionEvent(progressionStatus, progression01, fields, false);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const ::ax::ValueMap &fields, bool mergeFields)
        {
            addProgressionEvent(progressionStatus, progression01, "", "", fields, mergeFields);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score)
        {
            addProgressionEvent(progressionStatus, progression01, "", "", score);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score, const ::ax::ValueMap &fields)
        {
            addProgressionEvent(progressionStatus, progression01, score, fields, false);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score, const ::ax::ValueMap &fields, bool mergeFields)
        {
            addProgressionEvent(progressionStatus, progression01, "", "", score, fields, mergeFields);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, "");
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const ::ax::ValueMap &fields)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, fields, false);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const ::ax::ValueMap &fields, bool mergeFields)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, "", fields, mergeFields);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, "", score);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score, const ::ax::ValueMap &fields)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, score, fields, false);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score, const ::ax::ValueMap &fields, bool mergeFields)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, "", score, fields, mergeFields);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03, "", false);
#endif
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, const ::ax::ValueMap &fields)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, progression03, fields, false);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03, score, "", false);
#endif
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const ::ax::ValueMap &fields)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, progression03, score, fields, false);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03, score, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addDesignEvent(const char *eventId)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addDesignEvent(eventId, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addDesignEvent(eventId, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addDesignEvent(eventId, "", false);
#endif
        }

        void GameAnalytics::addDesignEvent(const char *eventId, const ::ax::ValueMap &fields)
        {
            addDesignEvent(eventId, fields, false);
        }

        void GameAnalytics::addDesignEvent(const char *eventId, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addDesignEvent(eventId, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addDesignEvent(eventId, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addDesignEvent(eventId, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addDesignEvent(const char *eventId, float value)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addDesignEventWithValue(eventId, value, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addDesignEventWithValue(eventId, value, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addDesignEvent(eventId, value, "", false);
#endif
        }

        void GameAnalytics::addDesignEvent(const char *eventId, float value, const ::ax::ValueMap &fields)
        {
            addDesignEvent(eventId, value, fields, false);
        }

        void GameAnalytics::addDesignEvent(const char *eventId, float value, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addDesignEventWithValue(eventId, value, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addDesignEventWithValue(eventId, value, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addDesignEvent(eventId, value, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addErrorEvent(EGAErrorSeverity severity, const char *message)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addErrorEvent((int)severity, message, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addErrorEvent((int)severity, message, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addErrorEvent((gameanalytics::EGAErrorSeverity)((int)severity), message, "", false);
#endif
        }

        void GameAnalytics::addErrorEvent(EGAErrorSeverity severity, const char *message, const ::ax::ValueMap &fields)
        {
            addErrorEvent(severity, message, fields, false);
        }

        void GameAnalytics::addErrorEvent(EGAErrorSeverity severity, const char *message, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addErrorEvent((int)severity, message, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addErrorEvent((int)severity, message, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::addErrorEvent((gameanalytics::EGAErrorSeverity)((int)severity), message, getStringFromValueMap(fields).c_str(), mergeFields);
#endif
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addAdEvent((int)adAction, (int)adType, adSdkName, adPlacement, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addAdEvent((int)adAction, (int)adType, adSdkName, adPlacement, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, const ::ax::ValueMap &fields)
        {
            addAdEvent(adAction, adType, adSdkName, adPlacement, fields, false);
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addAdEvent((int)adAction, (int)adType, adSdkName, adPlacement, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addAdEvent((int)adAction, (int)adType, adSdkName, adPlacement, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, int duration)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addAdEventWithDuration((int)adAction, (int)adType, adSdkName, adPlacement, duration, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addAdEventWithDuration((int)adAction, (int)adType, adSdkName, adPlacement, duration, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, int duration, const ::ax::ValueMap &fields)
        {
            addAdEvent(adAction, adType, adSdkName, adPlacement, duration, fields, false);
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, int duration, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addAdEventWithDuration((int)adAction, (int)adType, adSdkName, adPlacement, duration, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addAdEventWithDuration((int)adAction, (int)adType, adSdkName, adPlacement, duration, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addAdEventWithNoAdReason((int)adAction, (int)adType, adSdkName, adPlacement, (int)noAdReason, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addAdEventWithNoAdReason((int)adAction, (int)adType, adSdkName, adPlacement, (int)noAdReason, "", false);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason, const ::ax::ValueMap &fields)
        {
            addAdEvent(adAction, adType, adSdkName, adPlacement, noAdReason, fields,  false);
        }

        void GameAnalytics::addAdEvent(EGAAdAction adAction, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason, const ::ax::ValueMap &fields, bool mergeFields)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::addAdEventWithNoAdReason((int)adAction, (int)adType, adSdkName, adPlacement, (int)noAdReason, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_addAdEventWithNoAdReason((int)adAction, (int)adType, adSdkName, adPlacement, (int)noAdReason, getStringFromValueMap(fields).c_str(), mergeFields);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::setEnabledInfoLog(bool flag)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setEnabledInfoLog(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setEnabledInfoLog(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setEnabledInfoLog(flag);
#endif
        }

        void GameAnalytics::setEnabledVerboseLog(bool flag)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setEnabledVerboseLog(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setEnabledVerboseLog(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setEnabledVerboseLog(flag);
#endif
        }

        void GameAnalytics::setEnabledManualSessionHandling(bool flag)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setEnabledManualSessionHandling(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setEnabledManualSessionHandling(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setEnabledManualSessionHandling(flag);
#endif
        }

        void GameAnalytics::setEnabledEventSubmission(bool flag)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setEnabledEventSubmission(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setEnabledEventSubmission(flag);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setEnabledEventSubmission(flag);
#endif
        }

        void GameAnalytics::setCustomDimension01(const char *customDimension)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setCustomDimension01(customDimension);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setCustomDimension01(customDimension);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setCustomDimension01(customDimension);
#endif
        }

        void GameAnalytics::setCustomDimension02(const char *customDimension)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setCustomDimension02(customDimension);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setCustomDimension02(customDimension);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setCustomDimension02(customDimension);
#endif
        }

        void GameAnalytics::setCustomDimension03(const char *customDimension)
        {
            lazySetWritablePath();
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::setCustomDimension03(customDimension);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_setCustomDimension03(customDimension);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            gameanalytics::GameAnalytics::setCustomDimension03(customDimension);
#endif
        }

        void GameAnalytics::startSession()
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::startSession();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_startSession();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        void GameAnalytics::endSession()
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            GameAnalyticsCpp::endSession();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            jni_endSession();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#endif
        }

        std::vector<char> GameAnalytics::getRemoteConfigsValueAsString(const char *key)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            return GameAnalyticsCpp::getRemoteConfigsValueAsString(key);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            return jni_getRemoteConfigsValueAsString(key);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            return gameanalytics::GameAnalytics::getRemoteConfigsValueAsString(key);
#endif
        }

        std::vector<char> GameAnalytics::getRemoteConfigsValueAsString(const char *key, const char *defaultValue)
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            return GameAnalyticsCpp::getRemoteConfigsValueAsString(key, defaultValue);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            return jni_getRemoteConfigsValueAsStringWithDefaultValue(key, defaultValue);
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            return gameanalytics::GameAnalytics::getRemoteConfigsValueAsString(key, defaultValue).data();
#endif
        }

        bool GameAnalytics::isRemoteConfigsReady()
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            return GameAnalyticsCpp::isRemoteConfigsReady();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            return jni_isRemoteConfigsReady();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            return gameanalytics::GameAnalytics::isRemoteConfigsReady();
#endif
        }

        std::vector<char> GameAnalytics::getRemoteConfigsContentAsString()
        {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
            return GameAnalyticsCpp::getRemoteConfigsContentAsString();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
            return jni_getRemoteConfigsContentAsString();
#elif (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
            return gameanalytics::GameAnalytics::getRemoteConfigsContentAsString().data();
#endif
        }

        void  GameAnalytics::lazySetWritablePath()
        {
            if (!isWritablePathSet)
            {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT) || (AX_TARGET_PLATFORM == AX_PLATFORM_TIZEN) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
                std::string writablePath = ::ax::FileUtils::getInstance()->getWritablePath() + "GameAnalytics";
                if(!::ax::FileUtils::getInstance()->isDirectoryExist(writablePath))
                {
                    ::ax::FileUtils::getInstance()->createDirectory(writablePath);
                }
                gameanalytics::GameAnalytics::configureWritablePath(writablePath);
#endif
                isWritablePathSet = true;
            }
        }
    }
}
