#include "User.h"
#include "SortedLinkedList.h"
#include "LinkedListNode.h"

using namespace std;

// Implement the functions in the "User.h"

User::User(){
	id = 0;
	name =" ";
	followers = new SortedLinkedList();
	followeds = new SortedLinkedList();
}

User::~User(){ 
	if (followers != nullptr) {
        delete followers;
    }
    if (followeds != nullptr) {
        delete followeds;
    }
}
int User::getId(){
	return id;
}
void User::setId(int id){
	this->id = id;
}
string User::getName(){
	return name;
}
void User::setName(std::string name){
	this->name = name;
}

bool User::addFollower(User *u){
	if (followers->add(u)){
		u->addFollowed(this);
		return true;
	}
	return false;
}

bool User::removeFollower(int userId){
	return followers->remove(userId);
	
	/*if(followers->remove(userId)){
		LinkedListNode *UserNode = followers->getPointerTo(userId);
		if (UserNode == nullptr)
			return false;
		User* follower = UserNode->u;
		
		follower->removeFollowed(this->id);
		return true;
	}
	return false;*/
}

bool User::addFollowed(User *u){
	return followeds->add(u);
}

bool User::removeFollowed(int userId){
	return followeds->remove(userId);
}

SortedLinkedList* User::getFollowers(){
	return followers;
}
