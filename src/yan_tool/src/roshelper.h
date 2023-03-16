// clang-format off
#ifndef ROSHELPER_H
#define ROSHELPER_H

#include <atomic>
#include <thread>
#include <vector>
// #include <QObject>

#ifndef NO_ROS_FLAG
#include "ros/ros.h"
#endif

const uint32_t INVALID_SIZE = 0xFFFFFFFF;

class RosHelper /*: public QObject*/
{
    // Q_OBJECT
public:
    static RosHelper *getInstance();
    std::string framewareVer_;
    std::string blocklyVer_;
    std::string sn_;
    uint32_t availableSpace_;
    uint32_t userDataSize_;

public:
    void rosInit();
    int lightRestoreSystem();
    int getEnergyModeEnabled(bool &enable);
    int setEnergyModeEnable(bool enable);
    int uploadLog(std::string data);
    void getFramewareVersion();
    void getBlocklyVersion();
    void getSn();
    void getAvailableSpace();
    void getUserDataSize();

    //signals:
    //    void restoreFinished();
    //    void energyMode(bool isSaving);
    //    void uploadLogResult(bool succeed);

private:
    explicit RosHelper();
#ifndef NO_ROS_FLAG
    ros::ServiceClient client_version_read_;
    ros::ServiceClient client_light_restore_;
    ros::ServiceClient client_get_en_saving_enable_;
    ros::ServiceClient client_set_en_saving_enable_;
    ros::ServiceClient client_log_upload_set_;

#endif
};

#endif // ROSHELPER_H

// clang-format on
