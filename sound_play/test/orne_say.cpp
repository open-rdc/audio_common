

#include <sound_play/sound_play.h>
#include <unistd.h>
#include <ros/ros.h>
#include <move_base/move_base.h>
#include <std_srvs/Trigger.h>
#include <string>

void sleepok(int t, ros::NodeHandle &nh){
    if (nh.ok()){
        sleep(t);
    }
}

class OrneSay{
public:
    void run();

    void goalCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg);
    bool reqStartWpNav(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);
private:
    bool init_frag;
    ros::NodeHandle nh;
    sound_play::SoundClient sc;
    sound_play::SoundClient quiet_sc;
    ros::Subscriber wp_sub = nh.subscribe("/move_base/goal", 1, &OrneSay::goalCallback, this);
    int goal_count=0;     //goalが飛んできた回数
};


void OrneSay::run(){
    while(ros::ok()){
        ros::spinOnce();
    }
}

//２つのノードで同時にサービスを受信できないため、最初のゴールが来たらナビゲーションが開始されたと判定する
void OrneSay::goalCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg){
    if(goal_count == 0){
        ROS_INFO("start way points navigation");
    }else{
        ROS_INFO("arrived way point");
    }
	goal_count ++;
}


int main(int argc, char **argv){
    ros::init(argc, argv, "orne_say");
    OrneSay orne_say;
    orne_say.run();
}
