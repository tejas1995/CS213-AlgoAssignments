#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Point 
{
    int x;
    int y;
};

Point *red_point;
Point *blue_point;

struct LineSegment
{
    int red_pt_index;
    int blue_pt_index;
};

vector<LineSegment> list_line_segments;

struct Division
{
    vector<int> list_red_pt_index;
    vector<int> list_blue_pt_index;
    int num_points;
};

int orientation(Point P1, Point P2, Point P3)
{
    double val = (P2.y - P1.y)*(P3.x - P2.x) - (P3.y - P2.y)*(P2.x - P1.y);

    return (val > 0) ? 1 : -1;
}

bool find_line_segments(Division division)
{

    Division new_ccw_division, new_cw_division;
    LineSegment div_ls;
    /*cout << "New Division\n\nRed Points: ";
    for(int i = 0; i < division.num_points; i++)
        cout << red_point[ division.list_red_pt_index[i] ].x << " " << red_point[ division.list_red_pt_index[i] ].y << ", ";

    cout << "\nBlue Points: ";
    for(int i = 0; i < division.num_points; i++)
        cout << blue_point[ division.list_blue_pt_index[i] ].x << " " << blue_point[ division.list_blue_pt_index[i] ].y << ", ";
    */

    int div_red_pt_index = division.list_red_pt_index[0];
    Point div_red_pt = red_point[ div_red_pt_index ];

    int div_blue_pt_index;
    Point div_blue_pt;

    for(int i = 0; i < division.num_points; i++)
    {
        div_blue_pt_index = division.list_blue_pt_index[i];
        div_blue_pt = blue_point[ div_blue_pt_index ];

        int num_red_pts_ccw = 0;
        int num_blue_pts_ccw = 0;
        for(int j = 0; j < division.num_points; j++)
        {
            if(division.list_red_pt_index[j] != div_red_pt_index)
                if(orientation(div_red_pt, div_blue_pt, red_point[ division.list_red_pt_index[j] ]) == 1)
                    num_red_pts_ccw++;
        }

        for(int j = 0; j < division.num_points; j++)
        {
            if(division.list_blue_pt_index[j] != div_blue_pt_index)
                if(orientation(div_red_pt, div_blue_pt, blue_point[ division.list_blue_pt_index[j] ]) == 1)
                    num_blue_pts_ccw++;
        }

        if(num_red_pts_ccw == num_blue_pts_ccw)
        {

            div_ls.red_pt_index = div_red_pt_index;
            div_ls.blue_pt_index = div_blue_pt_index;

            //cout << "\nDivision LS: \n";
            //cout << red_point[div_red_pt_index].x << " " << red_point[div_red_pt_index].y << endl;
            //cout << blue_point[div_blue_pt_index].x << " " << blue_point[div_blue_pt_index].y << endl;

            for(int j = 0; j < division.num_points; j++)
            {
                if(division.list_red_pt_index[j] != div_red_pt_index)
                {
                    if(orientation(div_red_pt, div_blue_pt, red_point[ division.list_red_pt_index[j] ]) == 1)
                        new_ccw_division.list_red_pt_index.push_back( division.list_red_pt_index[j] );
                    else
                        new_cw_division.list_red_pt_index.push_back( division.list_red_pt_index[j] );
                }
            }

            for(int j = 0; j < division.num_points; j++)
            {
                if(division.list_blue_pt_index[j] != div_blue_pt_index)
                {
                    if(orientation(div_red_pt, div_blue_pt, blue_point[ division.list_blue_pt_index[j] ]) == 1)
                        new_ccw_division.list_blue_pt_index.push_back( division.list_blue_pt_index[j] );
                    else
                        new_cw_division.list_blue_pt_index.push_back( division.list_blue_pt_index[j] );
                }
            }

            new_ccw_division.num_points = num_red_pts_ccw;
            new_cw_division.num_points = division.num_points - 1 - num_red_pts_ccw;
            break;

        }

    }

    list_line_segments.push_back(div_ls);
    //cout << "-------------------------\n";

    if(new_ccw_division.num_points > 0)
        find_line_segments(new_ccw_division);

    if(new_cw_division.num_points > 0)
        find_line_segments(new_cw_division);

}

int main()
{
    int n;
    cin >> n;
    n = n/2; //n = No. of red points = No. of blue points

    red_point = new Point [n];
    blue_point = new Point [n];
    Division overall_division;

    for(int i = 0; i < n; i++)
    {
        cin >> red_point[i].x >> red_point[i].y;
        overall_division.list_red_pt_index.push_back(i);
    }

    for(int i = 0; i < n; i++)
    {
        cin >> blue_point[i].x >> blue_point[i].y;
        overall_division.list_blue_pt_index.push_back(i);
    }

    overall_division.num_points = n;
    find_line_segments(overall_division);

    for(int i = 0; i < list_line_segments.size(); i++)
    {
        cout << list_line_segments[i].red_pt_index << " " << list_line_segments[i].blue_pt_index << endl;
    }

    return 0;
}