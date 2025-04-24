/*
 * Description:
 * Low level design framework for stack overflow.
 *
 * Created on: 4/24/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef STACKOVERFLOW_H
#define STACKOVERFLOW_H

#include <iostream>
#include <map>
#include <vector>

class SO_Bounty;
class SO_Tag;
class SO_Comment;
class SO_Answer;
class SO_Question;
class SO_Badge;

/**************************** *  * enums *  * *************************************************************************/
enum SO_AccountStatus {
  SO_AS_ACTIVE,
  SO_AS_INACTIVE,
  SO_AS_BLOCKED
};

enum SO_QuestionStatus {
  SO_QS_ACTIVE,
  SO_QS_CLOSED,
  SO_QS_FLAGGED,
  SO_QS_BOUNTIED
};

enum SO_QuestionClosingReason {
  SO_QCR_OPINION_BASED,
  SO_QCR_NEED_MORE_CLARITY,
  SO_QCR_DUPLICATE,
  SO_QCR_COMMUNITY_SPECIFIC
};

/**************************** *  * Account *  * ***********************************************************************/
class SO_Account {
private:
  std::string name;
  std::string accountId;
  std::string username;
  std::string password;
  std::string mobileNumber;
  std::string emailId;
  SO_AccountStatus accountStatus;
};

/**************************** *  * User: Admin, moderator *  * *************************************************/
class SO_User {
  private:
  SO_Account account;
  double reputationPoints;
  std::vector<SO_Badge> badges;

public:
  void PostQuestion(SO_Question question);
  void PostAnswer(SO_Question question, SO_Answer answer);
  void PostComment(SO_Comment comment);
  void FlagQuestion(SO_Question question);
  void CreateTag();
  void AddTag();
  void Upvote();
  void DownVote();
  void VoteToCloseQuestion(SO_Question question);
  void VoteRToDeleteQuestion(SO_Question question);
  void AcceptAnswer(SO_Answer answer);
};

class SO_Admin : public SO_User {
public:
  void BlockAccount(SO_User user);
  void UnblockAccount(SO_User user);
  void AwardBadge(SO_User user, SO_Badge badge);
};

class SO_Moderator : public SO_User {
  public:
  void CloseQuestion(SO_Question question);
  void DeleteQuestion(SO_Question question);
  void ReOpenQuestion(SO_Question question);
  void DeleteAnswer(SO_Answer answer);
};

/**************************** *  * Guest *  * *************************************************************************/
/*
 * NOTE: Because the guest account cannot post question/answer, hence it is not derived from class SO_User.
 * So, it is an independent class.
 */
class SO_Guest {
  public:
  void RegisterAccount();
  void SearchQuestion(SO_Question question);
};

/**************************** *  * Question *  * *************************************************************************/
class SO_Question {
private:
  std::string questionId;
  std::string title;
  std::string content;

  time_t createdAt;
  time_t lastUpdatedAt;
  SO_User createdBy;

  //stats.
  int viewCount;
  int upvotes;
  int downvotes;
  int totalVoteCount;

  SO_Bounty *bounty;
  SO_QuestionClosingReason closingReason;

  //status.
  SO_QuestionStatus questionStatus;

  std::vector<SO_Tag> tags;
  std::vector<SO_Answer> answers;
  std::vector<SO_Comment> comments;
  std::vector<SO_User> followers;

public:
  void AddAnswer(SO_Answer answer);
  void AddComment(SO_Comment comment);
  void FollowQuestion(SO_User user);
};

/**************************** *  * Answer *  * ************************************************************************/
class SO_Answer {
  private:
  //Answer details.
  std::string answerId;
  std::string content;
  time_t createdAt;
  time_t lastUpdatedAt;
  SO_User postedBy;

  bool isAccepted;

  //stats
  int viewCount;
  int upvotes;
  int downvotes;
  int totalVoteCount;

  std::vector<SO_Comment> comments;
  std::vector<SO_User> followers;

  public:
  void AddComment(SO_Comment comment);
};

/**************************** *  * Comment *  * ***********************************************************************/
class SO_Comment {
  private:
  std::string commentId;
  std::string content;
  time_t createdAt;
  time_t lastUpdatedAt;
  SO_User postedBy;

  int upvotes;
  int downvotes;
  int totalVoteCount;
};

/**************************** *  * Bounty *  * ************************************************************************/
class SO_Bounty {
  private:
  double bountyPoints;
  time_t expiryDate;

public:
  void UpdateReputationPoints(double reputationPoints);
};

/**************************** *  * Tag and TagList *  * ***************************************************************/
class SO_Tag {
  private:
  std::string tagName;
  std::string description;
};

class SO_TagList {
  private:
  std::map<SO_Tag, int> tagCount;

public:
  void IncrementTagCount(SO_Tag tag);
  void DecrementTagCount(SO_Tag tag);
};

/**************************** *  * Badge *  * *************************************************************************/
class SO_Badge {
  private:
  std::string badgeName;
  std::string description;
};

/**************************** *  * Notification *  * ******************************************************************/
class SO_Notification {
  private:
  std::string notificationId;
  std::string content;
  time_t createdAt;

public:
  void SendNotification(SO_Account account);
  void SendNotification(SO_User user);
};

/**************************** *  * Search: Catalog *  * ***************************************************************/
class SO_Search {
public:
  virtual std::vector<SO_Question> SearchQuestionByTag(SO_Tag tag) = 0;
  virtual std::vector<SO_Question> SearchQuestionByUser(SO_User user) = 0;
  virtual std::vector<SO_Question> SearchQuestionByWord(std::string word) = 0;
};

class SO_Catalog : public SO_Search {
  private:
  std::map<SO_Tag, std::vector<SO_Question>> questionsByTag;
  std::map<SO_User, std::vector<SO_Question>> questionsByUser;
  std::map<std::string, std::vector<SO_Question>> questionsByWord;

  public:
  std::vector<SO_Question> SearchQuestionByTag(SO_Tag tag) override;
  std::vector<SO_Question> SearchQuestionByUser(SO_User user) override;
  std::vector<SO_Question> SearchQuestionByWord(std::string word) override;
};
/**************************** *  * END *  * ***************************************************************************/

#endif //STACKOVERFLOW_H
