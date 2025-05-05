/*
 * Description:
 * Low level design framework for facebook system design.
 *
 * Created on: 5/5/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef FACEBOOK_H
#define FACEBOOK_H

#include <iostream>
#include <vector>
#include <map>

class FB_Profile;
class FB_Comment;
class FB_Post;
class FB_User;
class FB_Group;
class FB_Page;

/****************** ** * Enums * ** ***********************************************************************************/
enum FB_AccountStatus {
  FB_AS_Active,
  FB_AS_Deactivated,
  FB_AS_Closed,
  FB_AS_Blocked
};

enum FB_FriendRequestStatus {
  FB_FRS_Pending,
  FB_FRS_Accepted,
  FB_FRS_Rejected,
  FB_FRS_Cancelled
};

enum FB_PostPrivacySetting {
  FB_PPS_Public,
  FB_PPS_Private,
  FB_PPS_OnlyFriends,
  FB_PPS_FriendsOfFriends,
  FB_PPS_Custom
};

/****************** ** * Address * ** *********************************************************************************/
class FB_Address {
private:
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipcode;
};

/****************** ** * Interfaces * ** ******************************************************************************/
class FB_PageFunctions {
  public:
  virtual FB_Page CreatePage(std::string pageName) = 0;
  virtual void DeletePage(FB_Page page) = 0;
  virtual void LikePage(FB_Page page) = 0;
  virtual void UnLikePage(FB_Page page) = 0;
  virtual void FollowPage(FB_Page page) = 0;
  virtual void UnFollowPage(FB_Page page) = 0;
  virtual void SharePage(FB_Page page) = 0;
};


class FB_GroupFunctions {
  public:
  virtual FB_Group CreateGroup(std::string groupName) = 0;
  virtual void DeleteGroup(FB_Group group) = 0;

  virtual void AddUserToGroup(FB_User user) = 0;
  virtual void RemoveUserFromGroup(FB_User user) = 0;
  virtual void SendGroupInvite(FB_Group group) = 0;

  virtual void JoinGroup(FB_Group group) = 0;
  virtual void LeaveGroup(FB_Group group) = 0;
};


class FB_PostFunctions {
  public:
  virtual FB_Post CreatePost(std::string content) = 0;
  virtual void DeletePost(FB_Post post) = 0;

  virtual void LikePost(FB_Post post) = 0;
  virtual void UnLikePost(FB_Post post) = 0;
  virtual void SharePost(FB_Post post) = 0;
  virtual void AddCommentToPost(FB_Post post) = 0;
};


class FB_CommentFunctions {
  public:
  virtual FB_Comment CreateComment(FB_Post post, std::string comment) = 0;
  virtual FB_Comment CreateComment(FB_Comment comment, std::string content) = 0;  //comment on comment.
  virtual void LikeComment(FB_Comment comment) = 0;
};

/****************** ** * Account * ** *********************************************************************************/
class FB_Account {
private:
  std::string accountId;
  std::string userName;
  std::string userPassword;
  std::string emailId;
  FB_AccountStatus status;
};

/****************** ** * Person, Admin: User * ** *********************************************************************/
class FB_Person {
  private:
  std::string name;
  FB_Address address;
  std::string phone;
  FB_Account account;
};

class FB_Admin {
public:
  void BlockUser(FB_User user);
  void UnBlockUser(FB_User user);
  void EnablePage(FB_Page page);
  void DisablePage(FB_Page page);
  void CreateGroup(FB_Group group);
  void DeleteGroup(FB_Group group);
  void ChangePrivacySettingsForGroup(FB_Group group);
};

class FB_User : public FB_Person,
                public FB_Account,
                public FB_PostFunctions,
                public FB_CommentFunctions,
                public FB_PageFunctions,
                public FB_GroupFunctions {
  private:
  std::string userId;
  time_t dateOfJoining;
  FB_Profile *profile;
  std::vector<FB_Page> pagesAdmin;
  std::vector<FB_Group> groupAdmin;

public:
  void SendFriendRequest(FB_User user);
  void AcceptFriendRequest(FB_User user);
  void RejectFriendRequest(FB_User user);

  void FollowUser(FB_User user);
  void UnFollowUser(FB_User user);
  void BlockUser(FB_User user);
  void UnBlockUser(FB_User user);
  void SendMessage(FB_User user, std::string content);

  //Implementation for functions for all interfaces
  //Page functions implementation
  FB_Page CreatePage(std::string pageName);
  void DeletePage(FB_Page page);
  void LikePage(FB_Page page);
  void UnLikePage(FB_Page page);
  void FollowPage(FB_Page page);
  void UnFollowPage(FB_Page page);
  void SharePage(FB_Page page);

  //Group function implementation
  FB_Group CreateGroup(std::string groupName);
  void DeleteGroup(FB_Group group);
  void AddUserToGroup(FB_User user);
  void RemoveUserFromGroup(FB_User user);
  void SendGroupInvite(FB_Group group);
  void JoinGroup(FB_Group group);
  void LeaveGroup(FB_Group group);

  //Post related functions implementation
  FB_Post CreatePost(std::string content);
  void DeletePost(FB_Post post);
  void LikePost(FB_Post post);
  void UnLikePost(FB_Post post);
  void SharePost(FB_Post post);
  void AddCommentToPost(FB_Post post);

  //Comment related functions implementation.
  FB_Comment CreateComment(FB_Post post, std::string comment);
  FB_Comment CreateComment(FB_Comment comment, std::string content);  //comment on comment.
  void LikeComment(FB_Comment comment);
};

/****************** ** * Education * ** *******************************************************************************/
class FB_Education {
  private:
  time_t startDate;
  time_t endDate;
  std::string description;
  std::string schoolName;
  std::string degree;
  std::string location;
};

/****************** ** * Work * ** ************************************************************************************/
class FB_Work {
  private:
  time_t startDate;
  time_t endDate;
  std::string companyName;
  std::string designation;
  std::string description;
  std::string location;
};

/****************** ** * Place * ** ***********************************************************************************/
class FB_Place {
  private:
  std::string name;
};

/****************** ** * Profile * ** *********************************************************************************/
class FB_Profile {
  private:
  std::string gender;
  time_t dateOfBirth;
  std::vector<unsigned char> profilePhoto;
  std::vector<unsigned char> coverPhoto;

  std::vector<FB_User> friends;
  std::vector<FB_Page> pagesFollowed;
  std::vector<FB_User> usersFollowed;
  std::vector<FB_Group> groupsFollowed;

  std::vector<FB_Work> workHistory;
  std::vector<FB_Education> educationHistory;
  std::vector<FB_Place> places;

public:
  void AddGender(std::string gender);
  void AddProfilePhoto(std::vector<unsigned char> photo);
  void AddCoverPhoto(std::vector<unsigned char> photo);
  void AddEducation(FB_Education education);
  void AddWork(FB_Work work);
};

/****************** ** * Page, Post, Comment * ** *********************************************************************/
class FB_Comment {
private:
  std::string commentId;
  std::string content;
  int likeCount;
  FB_User commentOwner;
};

class FB_Page {
  private:
  std::string pageId;
  std::string name;
  std::string description;
  int likeCount;
};

class FB_Post {
  private:
  std::string postId;
  std::string content;
  std::vector<FB_User> tags;
  std::vector<std::vector<unsigned char>> photos;
  FB_PostPrivacySetting postPrivacy;
  FB_User postOwner;

  int likeCount;
  int sharesCount;
  std::vector<FB_Comment> comments;
};

/****************** ** * Profile privacy interface * ** ***************************************************************/
class FB_ProfilePrivacy {
public:
  virtual void LockProfile(FB_Profile profile) = 0;
  virtual void LockProfilePic(FB_Profile profile) = 0;
};

/****************** ** * Group * ** ***********************************************************************************/
class FB_Group {
private:
  std::string groupId;
  std::string name;
  std::string description;
  int membersCount;
  FB_User groupOwner;
  std::vector<FB_User> members;
  bool isPrivate;

  public:
  void AddMember(FB_User member);
  void RemoveMember(FB_User member);
};

/****************** ** * Message * ** *********************************************************************************/
class FB_Message {
  private:
  std::string messageId;
  std::string content;
  FB_User sender;
  std::vector<FB_User> recipients;
  std::vector<unsigned char> multimedia;

public:
  void AddRecipient(FB_User recipient);
};

/****************** ** * Friend Request * ** **************************************************************************/
class FB_MessageRequest {
  private:
  FB_User sender;
  FB_User recipient;
  FB_FriendRequestStatus frStatus;
  time_t sentOn;

public:
  void CancelRequest();
};

/****************** ** * Notification * ** ****************************************************************************/
class FB_Notification {
  private:
  std::string notificationId;
  std::string content;
  time_t sentAt;

  public:
  void SendNotification();
};

/****************** ** * Search and Catalog * ** **********************************************************************/
class FB_Search {
public:
  virtual std::vector<FB_User> SearchUsers(std::string name) = 0;
  virtual std::vector<FB_Group> SearchGroups(std::string name) = 0;
  virtual std::vector<FB_Page> SearchPages(std::string name) = 0;
  virtual std::vector<FB_Post> SearchPosts(std::string keywords) = 0;
};

class FB_Catalog : public FB_Search {
private:
  std::map<std::string, std::vector<FB_User>> users;
  std::map<std::string, std::vector<FB_Group>> groups;
  std::map<std::string, std::vector<FB_Page>> pages;
  std::map<std::string, std::vector<FB_Post>> posts;

  public:
  std::vector<FB_User> SearchUsers(std::string name);
  std::vector<FB_Group> SearchGroups(std::string name);
  std::vector<FB_Page> SearchPages(std::string name);
  std::vector<FB_Post> SearchPosts(std::string keywords);
};

/****************** ** * End * ** *************************************************************************************/
#endif //FACEBOOK_H
