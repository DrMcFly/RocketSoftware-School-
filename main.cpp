#include<iostream>
#include<fstream>
#include<chrono>
#include<iomanip>
#include<random>
#include<stdint.h>

#define ROCKET_ID "000001"
#define ROCKET_NAME "XR-1"
#define ROCKET_VERSION "1.0"
#define SOFTWARE_VERSION "1.0"


class flight_metrics {
    public:
    
    void update()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        double a = 1.0;
        double b = 10.0;

        std::uniform_real_distribution<double> uniformDist(a, b);

        roll = getRoll((int)uniformDist(gen)^2);
        pitch = getPitch((int)uniformDist(gen)^2);
        yaw = getYaw((int)uniformDist(gen)^2);
        acceleration = getAccel((int)uniformDist(gen)^2);
    }
    
    short int roll{ getRoll(5) };
    short int roll_rate{ 0 };

    short int pitch{ getPitch(5) };
    short int pitch_rate{ 0 };

    short int yaw{ getYaw(5) };
    short int yaw_rate{ 0 };

    short int acceleration{ getAccel(5) };

    u_int8_t internal_temp{ 0 };

    short airspeed{ 0 };
    short speed{ 0 };

    unsigned short altitude{ 0 };

    struct GPS
    {
        std::string ID { "_001_" };
        std::string Base_ID { "-" };
        std::string WGS84_Lat { "" };
        std::string WGS84_Long { "" };
        enum position { fixed, dynamic };
        u_int8_t satellites_used { 0 };

        struct coordinate
        {
            enum direction{N, W, S, E};
            
            short degrees{ 32 };
            short minutes{ 42 };
            float seconds{ 72.354 };

            std::string displayCoord()
            {
                char* temp  = new char;

                // switch (direction)
                // {
                // case N:
                //     *temp = 'N';
                //     break;
                // case W:
                //     *temp = 'W';
                //     break;
                // case S:
                //     *temp = 'S';
                //     break;
                // case E:
                //     *temp = 'E';
                //     break;           
                // default:
                //     break;
                // }

                return *temp + std::to_string(degrees) + "°" + std::to_string(minutes) + "'" + std::to_string(seconds) + "\"";
            }

        };

    };
    


    
    
    private:
    short int getRoll(int value) 
    {
        return value;
    }
    short int getPitch(int value) 
    {
        return value;
    }
    short int getYaw(int value) 
    {
        return value;
    }
    short int getAccel(int value)
    {
        return value;
    }

};

std::string getMillisecondTimestamp() {
    // Get the current time point
    auto currentTimePoint = std::chrono::system_clock::now();

    // Convert the time point to milliseconds
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()).count();

    // Convert the timestamp to a string
    std::stringstream timestampStream;
    timestampStream << std::put_time(std::localtime(&millis), "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << millis % 1000;

    return timestampStream.str();
}

bool init_file(std::fstream& file, std::string filename);

int main() {
    flight_metrics rocket;
    std::fstream accel_data;
    
    init_file(accel_data, "data.txt");
    

    auto currentTimePoint = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
    std::string timestamp = std::ctime(&currentTime);

    flight_metrics::GPS::coordinate example;

    std::cout << example.displayCoord() << std::endl;

    


    for (int i = 1; i <= 1000; i++)
    {
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()).count();
        currentTimePoint = std::chrono::system_clock::now();
        accel_data << getMillisecondTimestamp() << ": {" << rocket.roll << "," << rocket.pitch << "," << rocket.yaw << "}" << std::endl;
        rocket.update();
    }

    accel_data.close();
    
    return 0;
}

bool init_file(std::fstream& file, std::string filename)
{
    
    file.open(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return false;
    }

    auto currentTimePoint = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
    std::string timestamp = std::ctime(&currentTime);

    {
        
        using namespace std;
        
        file << "==============================================================================" << endl;
        file << "Rocket Telemetry Data File" << endl;
        file << timestamp;
        file << "------------------------------------------------------------------------------" << endl;
        // file << endl;
        file << "Rocket Name: \"" << ROCKET_NAME << "\"" << endl;
        file << "Rocket ID: " << ROCKET_ID << endl;
        file << "Rocket Version: " << ROCKET_VERSION << endl;
        // file << endl;
        file << "------------------------------------------------------------------------------" << endl;
        // file << endl;
        file << "Software Version: " << SOFTWARE_VERSION << endl;
        file << "Programming Language: " << "C++(23)" << endl;
        // file << endl;
        file << "------------------------------------------------------------------------------" << endl;
        // file << endl;
        file << "Created and maintained by Martin McCorkle" << endl;
        file << "==============================================================================" << endl;
        file << endl;

    }


    
    return true;
}