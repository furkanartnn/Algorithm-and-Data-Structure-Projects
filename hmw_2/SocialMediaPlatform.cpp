#include "SocialMediaPlatform.h"
#include "User.h"
#include "SortedLinkedList.h"
#include "LinkedListNode.h"

using namespace std;

// Implement functions in the "SocialMediaPlatform.h"

SocialMediaPlatform::SocialMediaPlatform(){
	users = new SortedLinkedList();
}
SocialMediaPlatform::~SocialMediaPlatform(){
	delete users;
	
}
bool SocialMediaPlatform::addUser(const int userId, const std::string name){
	if(users->checkIfExist(userId)){
		//cout<< "User with ID "<< userId << "already exists." << endl;
		return false;
	}

	User *user = new User();
	user->setId(userId);
	user->setName(name);
	return users->add(user);
}
bool SocialMediaPlatform::removeUser(const int userId){
	
	LinkedListNode *tmp = users->getPointerTo();

	if (users->checkIfExist(userId))
	{
		
		while (tmp)
		{
			//cout << "userId: " << userId  << "| tmp->u->getıd() : "  << tmp->u->getId() << endl;
			//getchar();
			unfollowUser(tmp->u->getId(), userId);
			unfollowUser(userId, tmp->u->getId());
			tmp = tmp->next;
		}
		return users->remove(userId);
	}
	return false;
}
bool SocialMediaPlatform::followUser(const int firstUserId, const int secondUserId){
	LinkedListNode *firstUserNode = users->getPointerTo(firstUserId);
	LinkedListNode *secondUserNode = users->getPointerTo(secondUserId);

	if (!firstUserNode || !secondUserNode)
		return false;
	User *firstUser = firstUserNode->u;
	User *secondUser = secondUserNode->u;
	return firstUser->addFollowed(secondUser) && secondUser->addFollower(firstUser);
		
}
bool SocialMediaPlatform::unfollowUser(const int firstUserId, const int secondUserId){
	LinkedListNode *firstUserNode = users->getPointerTo(firstUserId);
	LinkedListNode *secondUserNode = users->getPointerTo(secondUserId);
	
	if (!firstUserNode || !secondUserNode)
		return false;
	User *firstUser = firstUserNode->u;
	User *secondUser = secondUserNode->u;
	bool a = firstUser->removeFollowed(secondUserId);
	bool b = secondUser->removeFollower(firstUserId);
	return a && b;
}
void SocialMediaPlatform::showFollowersOf(const int userId) const{
	LinkedListNode* userNode = users->getPointerTo(userId);
	if(userNode==nullptr){
		cout<<"Cannot show. There is no user with ID " << userId << "."<<endl;
		return;
	}
	User *user = userNode->u;
	SortedLinkedList *followers = user->getFollowers();
	if(followers!= nullptr){
		cout << "Users following the user with ID " << userId << ":"<< endl;
		followers->print();	
	}
	else{
		cout << "No followers found for user with ID: "<< userId << endl;
	}
	
}
void SocialMediaPlatform::showAllUsers() const {
	cout << "Users in the social media platform:"<<endl;
	users->print();
}
