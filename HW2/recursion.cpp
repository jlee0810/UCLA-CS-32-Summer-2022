#include <iostream>
#include <string>
using namespace std;

int multiplyTwoNumbers(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0 ) {
        return 0;
    }

    int sumBefore = multiplyTwoNumbers(m , n - 1);
    return m + sumBefore;
}

int tabulationStation(int num, int digit) {
    if (num == 0) {
        return 0;
    }
    if (num < 0 ) {
        num = num * -1;
    }

    int prevCount = tabulationStation((num / 10), digit);
    if (num % 10 == digit) {
        prevCount += 1;
    }

    return prevCount;
}

string highFives(string n) {
    if (n.length() == 0 || n.length() == 1) {
        return n;
    }

    if (n[0] == n[1]) {
        return n.substr(0, 1) + "55" + highFives(n.substr(1));
    }
    
    return n[0] + highFives(n.substr(1));
}

string jheriCurls(string str) {
    if (str.length() == 0) { //Base case when string is empty
        return str;
    }

    if (str[0] == '{'){
        if (str[str.length() - 1] == '}') { //Found the } at the end
            return str; //return the string with the curly braces
        }
        else {
            return jheriCurls(str.substr(0, str.length() - 1)); //Since the last element is not the }, shrink the string from the right by 1
        }
    }
    return jheriCurls(str.substr(1)); //Since first element is not { shrink the string from the left by 1
}

bool aggregationNation(const int a[], int size, int target) 
{
    if (size < 0) {
        return false; //size is negative therefore false
    }
    if (target == 0) { //If the target number is 0 -> always true as the combination can just be an empty array
        return true;
    }
    if (size == 0) { //At this point, the target number is not 0 and the array is empty -> always false
        return false;
    }
    bool until_now = aggregationNation(a + 1, size - 1, target); //Recursive function - check if the target can be achieved by adding the elements of the array a minus the first element
    if (until_now) { //if it can return true and we know that there is a combination
        return true;
    }

    return aggregationNation(a + 1, size - 1, target - a[0]); //Recursive function - check if the target - first element can be achieved by the array a minus the first element
} 

bool onMyWayHome(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec) { //If the start location is equal to the ending location, then we've solved the maze, so return true.
        return true;
    }
    maze[sr][sc] = '#'; //Mark the start location as visited (with #)

    //Explore North, South, East, West
    if (sr - 1 >= 0 && maze[sr - 1][sc] == '.') { //If the location one step north is unvisited
        if (onMyWayHome(maze, nRows, nCols, sr - 1, sc, er, ec)) { // then call onMyWayHome starting from that location and ending at the same ending location as in the current call
            return true; //if that returned true then return true
        }
    }

    if (sr + 1 < nRows && maze[sr + 1][sc] == '.') { //If the location one step south is unvisited
        if (onMyWayHome(maze, nRows, nCols, sr + 1, sc, er, ec)) { //then call onMyWayHome starting from that location and ending at the same ending location as in the current call
            return true; //if that returned true then return true
        }
    }

    if (sc + 1 < nCols && maze[sr][sc + 1] == '.') { //If the location one step east is unvisited
        if (onMyWayHome(maze, nRows, nCols, sr, sc + 1, er, ec)) { //then call onMyWayHome starting from that location and ending at the same ending location as in the current call
            return true; //if that returned true then return true
        }
    }

    if (sc - 1 >= 0 && maze[sr][sc - 1] == '.') { //If the location one step west is unvisited
        if (onMyWayHome(maze, nRows, nCols, sr, sc - 1, er, ec)) { //then call onMyWayHome starting from that location and ending at the same ending location as in the current call
            return true; //if that returned true then return true
        }
    }
    return false; //This maze is unsolvable so return false
}

int main() 
{
}