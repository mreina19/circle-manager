#include <iostream>
#include <stdexcept>    //exceptions
#include <limits>       //numeric_limits<streamsize>::max()
#include <string>       //string type
#include <vector>       //vector type
#include <sstream>      //toStr() function
#include <iomanip>      //setprecision()

#include "circle.h"

using namespace std;

//Returns a string (number) with two decimal cases
string toStr(float val, int decimals = 2) {
    ostringstream oss;
    oss << fixed << setprecision(decimals) << val;
    return oss.str();
}

enum class BoxStyle { Error, Warning, Success, Negative, Info };

//ANSI color codes
namespace Color {
    const string Reset = "\033[0m";     //Default color
    const string Red = "\033[31m";
    const string Green = "\033[32m";
    const string Yellow = "\033[33m";
    const string Magenta = "\033[35m";
    const string Cyan = "\033[36m";
}

//Prints a colored, prefixed message to the console using ANSI color codes.
void printMsg(const vector<string>& lines, BoxStyle style = BoxStyle::Info)
{
    string prefix, color;

    switch (style)
    {
        case BoxStyle::Error:   
			prefix = "[!!] "; 
			color = Color::Red;    
			break;
			
        case BoxStyle::Warning: 
			prefix = "[!] "; 
			color = Color::Magenta; 
			break;
			
        case BoxStyle::Success: 
			prefix = "[+] "; 
			color = Color::Green;  
			break;

        case BoxStyle::Negative: 
			prefix = "[-] "; 
			color = Color::Yellow;  
			break;
			
        case BoxStyle::Info:
        default:
			prefix = "[i] "; 
			color = Color::Cyan;   
			break;
    }

    cout << color << "\n";

    //First line gets the prefix (e.g "[i] "), remaining lines are indented with spaces to align
    for (size_t i = 0; i < lines.size(); ++i)
        cout << (i == 0 ? prefix : string(prefix.size(), ' ')) << lines[i] << "\n";

    //After printing, the console text is reset to the default color
    cout << Color::Reset << "\n";
}

void printMenu()
{
    cout << "----------------------------------------\n"
		 << "1- Check position.\n"
         << "2- Check radius.\n"
         << "3- Check perimeter.\n"
         << "4- Check area.\n"
         << "5- Check quadrant.\n"
         << "6- Change position.\n"
         << "7- Change radius.\n"
         << "8- Check the distance to another circle.\n"
         << "9- Check if a point is inside the circle.\n"
         << "10- Exit program.\n\n"
         << "Option: ";
}

//Executes the selected operation
void executeOperation(short opc, Circle& c1)
{
    switch (opc)
    {
        case 1:
        {
            FloatXY pos = c1.position();
            printMsg({ "Position: (" + toStr(pos.x) + ", " + toStr(pos.y) + ")" });
            break;
        }

        case 2:
            printMsg({ "Radius: " + toStr(c1.size()) });
            break;

        case 3:
            printMsg({ "Perimeter: " + toStr(c1.perimeter()) });
            break;

        case 4:
            printMsg({ "Area: " + toStr(c1.area()) });
            break;

        case 5:
        {
            string quad = c1.quadrantStr();

            if (quad == "NONE")
                printMsg({ "The circle does not belong to any quadrant." }, BoxStyle::Negative);
            else
                printMsg({ "Quadrant: " + quad });

            break;
        }

        case 6:
        {
            float dx, dy;
            FloatXY pos = c1.position();

            while (true)
            {
                printMsg({
                    "Current circle coordinates: (" + toStr(pos.x) + ", " + toStr(pos.y) + ").",
                    "The values you enter will be added to them."
                });

                cout << "Enter x and y separated by a space: ";

                try {
                    cin >> dx >> dy;
                    break;
                }
                catch (const ios_base::failure&) {
                    printMsg({ "Error: Invalid input. Please try again." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (dx == 0.0f && dy == 0.0f)
                printMsg({ "Coordinates were not changed." }, BoxStyle::Negative);
            else {
                c1.move({ dx, dy });
                printMsg({ "Circle successfully moved." }, BoxStyle::Success);
            }

            break;
        }

        case 7:
        {
            float zoom;

            while (true)
            {
                printMsg({
                    "Current circle radius: " + toStr(c1.size()),
                    "The inserted value acts as a multiplier."
                });

                cout << "Zoom: ";

                try {
                    cin >> zoom;
                    c1.resize(zoom);
                    break;
                }
                catch (const ios_base::failure&) {
                    printMsg({ "Error: Invalid input. Please try again." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                catch (const invalid_argument& e) {
                    printMsg({ string("Error: ") + e.what() }, BoxStyle::Error);
                }
            }

            if (zoom == 1.0f)
                printMsg({ "Circle size was not changed." }, BoxStyle::Negative);
            else
                printMsg({ "Circle size changed successfully." }, BoxStyle::Success);

            break;
        }

        case 8:
        {
            float radius, x, y;

            while (true)
            {
                printMsg({ "Enter radius and coordinates for the second circle: <radius> <x> <y>." });

                cout << "Circle attributes: ";

                try
                {
                    cin >> radius >> x >> y;
                    Circle c2(radius, x, y);

                    float distance = c1.perimetersDistance(c2);
                    FloatXY pos = c1.position();

                    string msg;

                    if (distance > 0.0f)
                        msg = "Distance between the circles: " + toStr(distance);
                    else if (distance == 0.0f)
                        msg = "The circles are touching each other.";
                    else
                        msg = "The circles are overlapping.";

                    printMsg({
                        "Main circle attributes: radius " + toStr(c1.size()) + ", (" + toStr(pos.x) + ", " + toStr(pos.y) + ").",
                        "New circle attributes: radius " + toStr(radius) + ", (" + toStr(x) + ", " + toStr(y) + ").",
                        msg
                    });

                    break;
                }
                catch (const ios_base::failure&) {
                    printMsg({ "Error: Invalid input. Please try again." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                catch (const invalid_argument& e) {
                    printMsg({ string("Error: ") + e.what() }, BoxStyle::Error);
                }
            }
            break;
        }

        case 9:
        {
            float x, y;
            FloatXY pos = c1.position();
            float radius = c1.size();

            while (true)
            {
                printMsg({
                    "Current circle attributes: radius " + toStr(radius) + ", (" + toStr(pos.x) + ", " + toStr(pos.y) + ").",
                    "Enter POSX and POSY: <POSX> <POSY>."
                });

                cout << "Point coordinates: ";

                try {
                    cin >> x >> y;
                    break;
                }
                catch (const ios_base::failure&) {
                    printMsg({ "Error: Invalid input. Please try again." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (c1.contains({ x, y }))
                printMsg({ "The point is inside the circle." }, BoxStyle::Success);
            else
                printMsg({ "The point is not inside the circle." }, BoxStyle::Negative);

            break;
        }

        case 10:
            cout << "Program ended.\n";
            break;

        default:
            printMsg({ "Select a number between 1 and 10." }, BoxStyle::Warning);
            break;
    }
}

int main()
{
    short opc;

    // Creating a circle -> Radius: 2, Coordinates: {3, 5}
    Circle c1(2, { 3, 5 });

    // Enable exceptions for failbit and badbit
    cin.exceptions(ios::failbit | ios::badbit);

    do
    {
        printMenu();

        try {
            cin >> opc;
        }
        catch (const ios_base::failure&)
        {
            printMsg({ "Error: Invalid input. Please enter a number." }, BoxStyle::Error);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        executeOperation(opc, c1);

    } while (opc != 10);

    return 0;
}
