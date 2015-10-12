#include <iostream>
#include <list>
#include <iomanip>
using namespace std;

struct ship
{
    int right_end;
    int left_end;
    int velocity;
    int lane_num;
};

struct time_interval
{
    float t_low;
    float t_high;
};

bool compare_time_int(time_interval time_int_1, time_interval time_int_2)
{
    return (time_int_1.t_low < time_int_2.t_low);
}

void print(time_interval t)
{
    cout << "(" << t.t_low << ", " << t.t_high << ")";
}

int main()
{
    int n, curr_ship = 0, u, v, w, t1, t2;
    cin >> n >> w >> u >> v >> t1 >> t2;
    list<ship> ship_list;
    list<time_interval> time_int_list;

    for(int i = 0; i < n; i++)
    {
        char dir;
        int v_dir;
        cin >> dir;
        

        int num_ships_in_lane;
        cin >> num_ships_in_lane;

        for(int j = 0; j < num_ships_in_lane; j++)
        {
            int len, head_pos;
            cin >> len >> head_pos;

            ship new_ship;
            if(dir == 'E')      //Ship headed east
            {
                new_ship.left_end = head_pos-len;
                new_ship.right_end = head_pos;
                new_ship.velocity = u;
            }
            else                //Ship headed west
            {
                new_ship.left_end = head_pos;
                new_ship.right_end = head_pos+len;
                new_ship.velocity = -1*u;   
            }
            new_ship.lane_num = i;

            ship_list.push_back(new_ship);
        }
    }

    list<ship>::iterator ship_iter;
    list<time_interval>::iterator time_int_iter;
    float time_low, time_high;
    int i = 0;
    for(ship_iter = ship_list.begin(), i = 0; ship_iter != ship_list.end(); ship_iter++, i++)
    {
        float left_cross_time = (-1.0*((*ship_iter).left_end))/((*ship_iter).velocity);
        float right_cross_time = (-1.0*((*ship_iter).right_end))/((*ship_iter).velocity);

        if(left_cross_time < right_cross_time)
        {
            time_low = left_cross_time - (((*ship_iter).lane_num+1)*w)/(float)v;
            time_high = right_cross_time - ((*ship_iter).lane_num*w)/(float)v;
        }
        else
        {
            time_low = right_cross_time - (((*ship_iter).lane_num+1)*w + w/2.0)/(float)v;
            time_high = left_cross_time - ((*ship_iter).lane_num*w + w/2.0)/(float)v;
        }

        bool new_time_interval = true;
        
        if(new_time_interval == true)
        {
            time_interval ti;
            ti.t_low = time_low;
            ti.t_high = time_high;
            time_int_list.push_back(ti);
        }
    }


    time_int_list.sort(compare_time_int);

    /*for(time_int_iter = time_int_list.begin(); time_int_iter != time_int_list.end(); time_int_iter++)
    {
        print((*time_int_iter));
        //cout << endl;
    }*/

    float prev_t_high = t1;
    float max_start_interval = 0;
    for(time_int_iter = time_int_list.begin(); time_int_iter != time_int_list.end(); time_int_iter++)
    {
        if((*time_int_iter).t_low >= t1 && (*time_int_iter).t_low <= t2)
        {
            if((*time_int_iter).t_low - prev_t_high > max_start_interval)
            {
                max_start_interval = (*time_int_iter).t_low - prev_t_high;
            }
            prev_t_high = (*time_int_iter).t_high;
        }
    }   
    cout << fixed << setprecision(8) << max_start_interval << endl; 

}