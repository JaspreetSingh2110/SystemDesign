/*
 * Description:
 * Low level system design framework for Meeting Scheduler.
 *
 * Created on: 4/18/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef MEETINGSCHEDULER_H
#define MEETINGSCHEDULER_H

#include <iostream>
#include <list>
#include <map>
#include <vector>

//Forward declarations.
class MeetingNotificationService;

/***************************  * Enums *  ******************************************************************************/
enum MeetingRoomStatus {
  MR_AVAILABLE,
  MR_BLOCKED
};
/***************************  * MeetingParticipant *  *******************************************************************************/
class MeetingParticipant {
private:
  std::string name;
  std::string email;
public:
  void RespondInvite(MeetingNotificationService invite);
};

/***************************  * Interval *  ***************************************************************************/
class Interval {
  private:
  int startTime;
  int endTime;
};

/***************************  * Meeting Room *  ***********************************************************************/
class MeetingRoom {
  private:
  int mRoomId;
  std::string mRoomName;
  int capacity;
  MeetingRoomStatus status;
  std::vector<Interval> bookedIntervals;
};

/***************************  * Meeting *  ****************************************************************************/
class Meeting {
  private:
  std::string meetingId;
  std::string subject;
  Interval interval;
  MeetingRoom meetingRoom;
  std::vector<MeetingParticipant> participants;
  int participantsCount;

  public:
  void AddParticipant(MeetingParticipant user);
};

/***************************  * Calendar *  ***************************************************************************/
class Calendar {
  private:
  //meeting for each day for next 6 months.
  //Map for <month, <date, <list of meetings>>>
  std::map<int, std::map<int, std::vector<Meeting>>> meetings;
  //NOTE: this can further more simplified as:
  // std::map<std::string, std::vector<Interval>> meetings;
  //where, string will hold, year+month+day as hash Key.
};

/***************************  * Meeting Notification Service *  *******************************************************/
class MeetingNotificationService {
  private:
  int notificationId;
  std::string content;
  int creationDate;

  public:
  void SendNotification(MeetingParticipant user);
  void CancelNotification(MeetingParticipant user);
};

/***************************  * Meeting Scheduler *  ******************************************************************/
class MeetingScheduler {
  private:
  MeetingParticipant scheduler;
  Calendar calendar;
  std::map<int, MeetingRoom> meetingRooms;  // floor mapped meeting rooms.
  MeetingNotificationService notificationService;

public:
  int ScheduleMeeting(std::vector<MeetingParticipant> participants, Interval interval); //Returns MeetingId
  void UpdateMeeting(std::vector<MeetingParticipant> participants, Interval interval);
  void CancelMeeting(std::vector<MeetingParticipant> participants, Interval interval);
  void CancelMeeting(int meetingId);
  void BookRoom(Interval interval);
  void ReleaseRoom(Interval interval);
  MeetingRoom FindMeetingRoom(Interval interval, int participantsCount);
};

/***************************  * End *  ********************************************************************************/


#endif //MEETINGSCHEDULER_H
