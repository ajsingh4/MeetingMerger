//
//  main.cpp
//  MeetingMerger
//
//  Created by Aj Gill on 10/3/19.
//  Copyright © 2019 Aj Gill. All rights reserved.
//

#include <iostream>
#include <vector>

// C++11 lest unit testing framework
using namespace std;

class Meeting {
private:
    // number of 30 min blocks past 9:00 am
    unsigned int startTime_;
    unsigned int endTime_;
    
public:
    Meeting(): startTime_(0), endTime_(0) {}
    
    Meeting(unsigned int startTime, unsigned int endTime) : startTime_(startTime), endTime_(endTime) {}
    
    unsigned int getStartTime() const {
        return startTime_;
    }
    
    void setStartTime(unsigned int startTime) {
        startTime_ = startTime;
    }
    
    unsigned int getEndTime() const {
        return endTime_;
    }
    
    void setEndTime(unsigned int endTime) {
        endTime_ = endTime;
    }
    
    bool operator==(const Meeting& other) const {
        return
        startTime_ == other.startTime_
        && endTime_ == other.endTime_;
    }
};

bool compareMeetingsByStartTime(const Meeting& firstMeeting, const Meeting& secondMeeting) {
    return firstMeeting.getStartTime() < secondMeeting.getStartTime();
};

//Function to write
vector<Meeting> mergeRanges(const vector<Meeting>& meetings) {
    //Create a copy and sort them by start time
    vector<Meeting> sortedMeetings(meetings);
    sort(sortedMeetings.begin(), sortedMeetings.end(), compareMeetingsByStartTime);
    
    // initialize result vector with the first meeting
    vector<Meeting> mergedMeetings;
    mergedMeetings.push_back(sortedMeetings.front());
    
    for(Meeting m : sortedMeetings) {
        Meeting lastMerged = mergedMeetings.back();
        if(m.getStartTime() <= lastMerged.getEndTime()) {
            lastMerged.setEndTime(max(lastMerged.getEndTime(), m.getEndTime()));
        }
        else{
            mergedMeetings.push_back(m);
        }
    }
    
    return mergedMeetings;
}

int main() {
    vector<Meeting> meetings = {Meeting(0, 1), Meeting(3, 5), Meeting(4, 8),
        Meeting(10, 12), Meeting(9, 10)};
    vector<Meeting> mergedMeetings = mergeRanges(meetings);
    for(Meeting m : mergedMeetings) {
        cout << "Begin time: " << m.getStartTime() << " End time: " << m.getEndTime() << "\n";
    }
}
