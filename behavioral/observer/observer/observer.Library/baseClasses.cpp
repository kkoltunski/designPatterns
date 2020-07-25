#include "baseClasses.h"

void observableObject::addObserver(observer* _observer) {
	observersList.push_back(_observer);
}

void observableObject::removeObserver() {

}