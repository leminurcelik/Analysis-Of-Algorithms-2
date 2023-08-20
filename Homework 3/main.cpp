//ANALYSIS OF ALGORITHMS 2 HOMEWORK 3
//Leminur Çelik - 150190085
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdbool.h>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;


class Input{
    private:
        string placeName; //Initialize place name
        string salonName; //Initialize salon name
        int capacity; //Initialize capacity
        string startAt; //Initialize start time
        string endAt; //Initialize end time
        int endHour; //Initialize end hour
        int endMin; //Initialize end minute
        int startHour; //Initialize start hour
        int startMin; //Initialize start minute
        string startDate; //Initialize starting date
        string endDate; //Initialize ending date
        int startDay; //Initialize starting day
        int endDay; //Initialize ending day
        int startMonth; //Initialize starting month
        int endMonth; //Initialize ending month
    public:
        //Constructor of Input
        Input(){};
        //Set Place Name
        void setPlaceName(string placeName){
            this->placeName = placeName;
        }
        //Get Place Name
        string getPlaceName(){
            return this->placeName;
        }
        //Set Salon Name
        void setSalonName(string salonName){
            this->salonName = salonName;
        }
        //Get Salon Name
        string getSalonName(){
            return salonName;
        }
        //Set Capacity
        void setCapacity(int capacity){
            this->capacity = capacity;
        }
        //Get Capacity
        int getCapacity(){
            return capacity;
        }
        //Set Starting Time
        void setStartAt(string startAt){
            this->startAt = startAt;
        }
        //Set Ending Time
        void setEndAt(string endAt){
            this->endAt = endAt;
        }
        //Get Starting Time
        string getStartAt(){
            return startAt;
        }
        //Get Ending Time
        string getEndAt(){
            return endAt;
        }
        //Set Ending Hour
        void setEndHour(string endHour){
            this->endHour = (stoi(endHour));
        }
        //Set Ending Minute
        void setEndMin(string endMin){
            this->endMin = (stoi(endMin));
        }
        //Get Ending Hour
        int getEndHour(){
            return endHour;
        }
        //Get Ending Min
        int getEndMin(){
            return endMin;
        }
        //Set Starting Hour
        void setStartHour(string startHour){
            this->startHour = (stoi(startHour));
        }
        //Set Starting Minute
        void setStartMin(string startMin){
            this->startMin = (stoi(startMin));
        }
        //Get Starting Hour
        int getStartHour(){
            return startHour;
        }
        //Get Starting Minute
        int getStartMin(){
            return startMin;
        }
        //Set Starting Date
        void setStartDate(string startDate){
            this->startDate = startDate;
        }
        //Set Ending Date
        void setEndDate(string end_date){
            this->endDate = end_date;
        }
        //Get Starting Date
        string getStartDate(){
            return startDate;
        }
        //Get Ending Date
        string getEndDate(){
            return endDate;
        }
        //Set Starting Day
        void setStartDay(string startDay){
            this->startDay = (stoi(startDay));
        }
        //Set Ending Day
        void setEndDay(string endDay){
            this->endDay = (stoi(endDay));
        }
        //Get Starting Day
        int getStartDay(){
            return startDay;
        }
        //Get Ending Day
        int getEndDay(){
            return endDay;
        }
        //Set Starting Month
        void setStartMonth(string startMonth){
            this->startMonth = (stoi(startMonth));
        }
        //Set Ending Month
        void setEndMonth(string endMonth){
            this->endMonth = (stoi(endMonth));
        }
        //Get Starting Month
        int getStartMonth(){
            return startMonth;
        }
        //Get Ending Month
        int getEndMonth(){
            return endMonth;
        }
};
//Compare time for places
bool compareTime(Input i1, Input i2){
        if (i1.getEndHour() == i2.getEndHour())
        {
            if (i1.getEndMin() == i2.getEndMin())
            {
                return i1.getCapacity() > i2.getCapacity();
            }
            return i1.getEndMin() < i2.getEndMin();
        }
        else
            return i1.getEndHour() < i2.getEndHour();
}
//Compare date for places
bool compareDate(Input i1, Input i2){
    if (i1.getEndMonth() == i2.getEndMonth())
    {
        if (i1.getEndDay() == i2.getEndDay())
        {
            return i1.getCapacity() > i2.getCapacity();
        }
        return i1.getEndDay() < i2.getEndDay();
    }
    else
        return i1.getEndMonth() < i2.getEndMonth();
}
//Binary search for finding available time of place
int binarySearch(Input input[], int start, int index)
{
    int low = start; 
    int high = index - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (input[mid].getEndHour() == input[index].getStartHour()){
            if (input[mid].getEndMin() <= input[index].getStartMin())
            {
                if (input[mid + 1].getEndHour() == input[index].getStartHour()){
                    if (input[mid+1].getEndMin() <= input[index].getStartMin())
                        low = mid + 1;
                    else
                        return mid;
                }
                else if (input[mid + 1].getEndHour() < input[index].getStartHour()){
                    low = mid + 1;
                }                    
                else{
                        return mid;
                }
            }
            else{
                high = mid - 1;
            }
            
        }
        else if(input[mid].getEndHour() < input[index].getStartHour()){
            if (input[mid + 1].getEndHour() == input[index].getStartHour()){
                if (input[mid+1].getEndMin() <= input[index].getStartMin())
                    low = mid + 1;
                else
                    return mid;
                }
                else if (input[mid + 1].getEndHour() < input[index].getStartHour()){
                    low = mid + 1;
                }                    
                else{
                        return mid;
                }
        }
        else
            high = mid - 1;
    }
    return -1;
}
//Binary search for finding available date of place
int binarySearchDate(Input input[], int index)
{
    int low = 0;
    int high = index - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (input[mid].getEndMonth() == input[index].getStartMonth()){
            if (input[mid].getEndDay() <= input[index].getStartDay())
            {
                if (input[mid + 1].getEndMonth() == input[index].getStartMonth()){
                    if (input[mid+1].getEndDay() <= input[index].getStartDay()){
                        low = mid + 1;
                    }
                    else{
                        return mid;
                    }
                }
                else if (input[mid + 1].getEndMonth() < input[index].getStartMonth()){
                    low = mid + 1;
                }                    
                else{
                    return mid;
                }
            }
            else{
                high = mid -1;
            }
            
        }
        else if(input[mid].getEndMonth() < input[index].getStartMonth()){
            if (input[mid + 1].getEndMonth() == input[index].getStartMonth()){
                if (input[mid+1].getEndDay() <= input[index].getStartDay())
                    low = mid + 1;
                else
                    return mid;
                }
                else if (input[mid + 1].getEndMonth() < input[index].getStartMonth()){
                    low = mid + 1;
                }                    
                else{
                    return mid;
                }
        }
        else
            high = mid - 1;
    }
    return -1;
}
//Find maximum number of chairs for each place
int findMaxChairs(Input *input, int start, int end, ofstream &bestEach)
{
    sort(input + start, input + end, compareTime); //Sort places according to finish time
    vector<Input> schedule;   
    int *array = new int[end-start];
    array[0] = input[start].getCapacity();
    vector<bool> taken (end-start, false);
    taken[0] = true; 
    int previous [end-start];
    previous[0] = -1;
    for (int i = start+1; i < end; i++)
    {
        int incChair = input[i].getCapacity();
        int l = binarySearch(input, start, i);
        if (l != -1){
            incChair += array[l-start];
        }
        if (incChair > array[i-start-1])
        {
            array[i-start] = incChair;
            taken[i-start] = true;
            previous[i-start] = l-start;
        }
        else{
            array[i-start] = array[i-start-1];
            previous[i-start] = i-start-1;
        }

    }
    int current = end - start - 1;
    while (current > -1)
    {
        if (taken[current]){
            schedule.push_back(input[current + start]);
        }
        current = previous[current];    
    }
    for (long int i = schedule.size() - 1; i >= 0; i--)
    {
        bestEach << schedule[i].getPlaceName() << "\t" << schedule[i].getSalonName() << "\t" << schedule[i].getStartAt() << " " <<schedule[i].getEndAt() << endl;
    }
    int result = array[end-start-1];
    delete[] array;
    return result;
}
//Find maximum revenue
int findMaxRevenue(Input *input, int end, ofstream &bestTour)
{
    sort(input, input + end, compareDate); //Sort date according to finish time
    vector<Input> schedule;
    int *array = new int[end];
    if (input[0].getEndMonth() > input[0].getStartMonth())
    {
        array[0] = ((31 - input[0].getStartDay()) + input[0].getEndDay()) * input[0].getCapacity();
    }
    else
        array[0] = (input[0].getEndDay() - input[0].getStartDay()) * input[0].getCapacity();

    vector<bool> taken (end, false);
    taken[0] = true; // First program is taken.
    int previous [end];
    previous[0] = -1;
    // Fill entries in table[] using recursive property
    for (int i = 1; i < end; i++)
    {
        // Find profit including the current job
        int incRevenue;
        if (input[i].getEndMonth() > input[i].getStartMonth())
        {
            incRevenue = ((31 - input[i].getStartDay()) + input[i].getEndDay()) * input[i].getCapacity();
        }
        else 
            incRevenue = (input[i].getEndDay()- input[i].getStartDay()) * input[i].getCapacity();
        int l = binarySearchDate(input, i);
        if (l != -1){
            incRevenue += array[l];
            
        }
        if (incRevenue > array[i-1])
        {
            array[i] = incRevenue;
            taken[i] = true;
            previous[i] = l;
        }
        else{
            array[i] = array[i-1];
            previous[i] = i-1;
        }
    }
    int current = end - 1;
    while (current != -1)
    {
        if (taken[current])
        {
            schedule.push_back(input[current]);
        }
        current = previous[current];    
    }

    for (long int i = schedule.size() - 1; i >= 0; i--)
    {
        bestTour << schedule[i].getPlaceName() << "     " << schedule[i].getStartDate() << " " <<schedule[i].getEndDate() << endl;
    }
    int revenue = array[end-1];
    delete[] array;
    return revenue;
}

int main(int argc, char **argv){
    string caseNo = argv[1];//Get the case number from command line
    string input1 = "inputs/case_" + caseNo + "/daily_schedule.txt";
    fstream daily(input1, ios::in);//Define the daily schedule file
    string input2 = "inputs/case_" + caseNo + "/capacity.txt";
    fstream capacity(input2, ios::in);//Define the capacity file
    string input3 = "inputs/case_" + caseNo + "/availability_intervals.txt";
    fstream availability(input3, ios::in);//Define the availability intervals file
    string input4 = "inputs/case_" + caseNo + "/assets.txt";
    fstream assets(input4, ios::in);//Define the assets file as file

    string output1 = "outputs/case" + caseNo + "/best_for_eachplace.txt";
    ofstream bestEach(output1, ios::out);//Define the output of best place for each file
    string output2 = "outputs/case" + caseNo + "/best_tour.txt";
    ofstream bestTour(output2, ios::out);//Define the output of best tour file

    vector<string> placeName;
    vector<string> salonName;
    vector<int> capacit;
    string PlaceName, SalonName, Place, place, salon, Capacity, cap;
    capacity >> PlaceName >> SalonName >> Capacity;
    //Read capacity file
    while (!(capacity.eof()))
    {
        capacity >> place >> salon >> cap;
        placeName.push_back(place);
        salonName.push_back(salon);
        capacit.push_back(stoi(cap));
    }

    string Start, End, start, end;
    vector<string> dailyPlace;
    vector<string> dailySalon;
    vector<string> START;
    vector<string> END;
    vector<int> each;
    daily >> PlaceName >> SalonName >> Start >> End;
    //Read daily schedule file
    while (!(daily.eof()))
    {
        daily >> place >> salon >> start >> end;
        dailyPlace.push_back(place);
        dailySalon.push_back(salon);
        START.push_back(start);
        END.push_back(end);
    }

    Input *input = new Input[dailyPlace.size()];
    for (long unsigned int i = 0; i < dailyPlace.size(); i++)
    {
        input[i].setPlaceName(dailyPlace[i]);
        input[i].setSalonName(dailySalon[i]);
        input[i].setStartAt(START[i]);
        input[i].setEndAt(END[i]);
    }

    string temp = input[0].getPlaceName();
    int count = 1;
    for (long unsigned int i = 1; i < dailyPlace.size(); i++)
    {
        if (temp == input[i].getPlaceName())
        {
            count++;
        }
        else{
            each.push_back(count);
            count = 0;
            temp = input[i].getPlaceName();
            i--;
        }
    }

    each.push_back(count);
    //Separate starting times into hours and minutes
    for (long unsigned int i = 0; i < START.size(); i++)
    {
        string t;
        stringstream x(input[i].getStartAt());
        int c = 0;
        while (getline(x, t, ':'))
        {
            if (c == 0)
            {
                input[i].setStartHour(t);
                c++;
            }
            else{
                input[i].setStartMin(t);
            }
        }
    }
    //Separate ending times into hours and minutes
    for (long unsigned int i = 0; i < END.size(); i++)
    {   
        string t;
        stringstream x(input[i].getEndAt());
        int c = 0;
        while (getline(x, t, ':'))
        {
            if (c == 0)
            {
                input[i].setEndHour(t);
                c++;
            }
            else{
                input[i].setEndMin(t);
            }
        }
    
    }

    for (long unsigned int j = 0; j < capacit.size(); j++)
    {
        for (long unsigned int i = 0; i < dailyPlace.size(); i++)
        {
            if(input[i].getPlaceName() == placeName[j])
            {
                if (input[i].getSalonName() == salonName[j])
                {

                    input[i].setCapacity(capacit[j]);
                }
            }
        }
    }
    
    string Place_Name, StartingDate, EndingDate, place_name, startingdate, enddate;
    vector<string> availabilityPlace;
    vector<string> StartDate;
    vector<string> EndDate;
    availability >> Place_Name >> StartingDate >> EndingDate;

    //Read availability intervals file
    while (!(availability.eof()))
    {
        availability >> place_name >> startingdate >> enddate;
        availabilityPlace.push_back(place_name);
        StartDate.push_back(startingdate);
        EndDate.push_back(enddate);
    }
    
    Input *availability_input = new Input[availabilityPlace.size()];

    for (long unsigned int i = 0; i < availabilityPlace.size(); i++)
    {
        availability_input[i].setPlaceName(availabilityPlace[i]);
        availability_input[i].setStartDate(StartDate[i]);
        availability_input[i].setEndDate(EndDate[i]);
    }
    //Separate starting dates into months and days
    for (long unsigned int i = 0; i < StartDate.size(); i++)
    {
        string t;
        stringstream x(availability_input[i].getStartDate());
        int c = 0;
        while (getline(x, t, '.'))
        {
            if (c == 0)
            {
                availability_input[i].setStartDay(t);
                c++;
            }
            else{
                availability_input[i].setStartMonth(t);

            }
        }
    }
    //Separate ending dates into months and days
    for (long unsigned int i = 0; i < EndDate.size(); i++)
    {   
        string t;
        stringstream x(availability_input[i].getEndDate());
        int c = 0;
        while (getline(x, t, '.'))
        {
            if (c == 0)
            {
                availability_input[i].setEndDay(t);
                c++;
            }
            else{
                availability_input[i].setEndMonth(t);
            }
        }
    }

    vector<string> bestName;
    vector<int> bestPlace;
    int e = 0;
    int k = 0;
    for (long unsigned int i = 0; i < each.size(); i++)
    {
        e += each[i];
        int best_for_each = findMaxChairs(input, k, e, bestEach);
        bestEach << dailyPlace[k] << " --> "  << best_for_each << endl; //Find maximum number of chairs of each place
        bestEach << endl;
        bestName.push_back(dailyPlace[k]);
        bestPlace.push_back(best_for_each);
        k = e;
    }

    for (long unsigned int k = 0; k < bestName.size(); k++)
    {
        for (long unsigned int j = 0; j < availabilityPlace.size(); j++)
        {
            if (availability_input[j].getPlaceName() == bestName[k])
            {
                availability_input[j].setCapacity(bestPlace[k]);   
            }
        }
    }

    int best_tour = findMaxRevenue(availability_input, availabilityPlace.size(), bestTour); //Find total revenue
    bestTour << "Total Revenue --> " << best_tour << endl;
}