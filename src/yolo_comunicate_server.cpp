//***************************************************************************************************
//***************************************************************************************************
//***                                                                                              ***
//***       ロボ班の皆さん                                                                           ***
//***       薛です。（2021年度R班の卒業生）                                                            ***
//***       関大から卒業しましたけれども、ちょこちょこ暇な時間潰しためにコーディングします    　　　　　　　　　　　***
//***       ROS1からROS2への変換を向かっている人はこのプログラムを参考になれたら嬉しい 　　　　　　　　　　      ***
//***       ROS2のエグいところはC++11以後の文法を使ってますね,ROS１よりハードルが高くになりました              ***
//***       引き継ぐものは姜さん（キョウ）                                                              ***
//***                                                                                              ***
//****************************************************************************************************
//****************************************************************************************************
#include <memory>
#include <sstream>
#include <vector>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class yolo_comunication : public rclcpp::Node{
public:
    //类自己的构造函数也是类的成员函数，所以也可以访问类自己的私有成员
    yolo_comunication(): Node("yolo_comunication_node"){
        this->declare_parameter<int>("zed2i_status", 0);//1というのはzedの接続が正常　０はzedがまだ整えていない
        this->declare_parameter<int>("yolo_mode", -1);//1は画像をyoloに送信　-1は送信停止

        //パラメータをゲート
        rclcpp::Parameter int_param=this->get_parameter("zed2i_status");
        m_zed2iConfirm = int_param.as_int();

        //lambda函数在此程序目前阶段，定义在构造函数里面没有出错，好像不能像普通函数一样定义在类内的public区域
        //ラムダ式による関数オブジェクトの定義
        auto Zed_Status_Confirm =
        [this](const int &confirm_num) -> void
        {
            if(confirm_num==0){
                RCLCPP_INFO(this->get_logger(), "Zed CAMERA USB port is not connected properly, or the IMAGE TOPIC is not generated yet.");
            }else{
                RCLCPP_INFO(this->get_logger(), "Start Subscribing to Images");
            }
        };
        Zed_Status_Confirm(m_zed2iConfirm);

    } 

private:
    int m_zed2iConfirm;
    int m_ActionMode;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
     /*ノードの生成*/
    auto node = std::make_shared<yolo_comunication>();
    rclcpp::spin_some(node);
    
    rclcpp::shutdown();
    return 0;
}
