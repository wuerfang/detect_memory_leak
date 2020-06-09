#include"track_new.h"

//#ifndef NDEBUG

#include <cstdlib>
#include <iostream>

TrackerNew tracker_new;//定义全局的类

bool TrackerNew::flag = false;

void* operator new(size_t size, const char *file, long line) {
	void *p = malloc(size);
	if (TrackerNew::flag)
		tracker_new.add(p, file, line);

	return p;
}

void* operator new(size_t size) {
	void *p = malloc(size);
	if (TrackerNew::flag)
		tracker_new.add(p, "unknow", -1);

	return p;
}

void operator delete(void *p) {
	if (TrackerNew::flag)
		tracker_new.remove(p);
	free(p);
}


TrackerNew::TrackerNew() :m_lock_count(0) {
	TrackerNew::flag = true;
}

TrackerNew::~TrackerNew() {
	TrackerNew::flag = false;
	dump();
}

void TrackerNew::add(void *p, const char *file, long line) {
	if (m_lock_count > 0)	
		return;
	Lock lock(*this);
	m_track[p] = TrackerNewIn(file, line);
	/*m_lock_count++;
	m_track[p] = TrackerNewIn(file, line);
	m_lock_count--;*/
}

void TrackerNew::remove(void *p) {
	if (m_lock_count > 0)
		return;
	Lock lock(*this);
	auto it = m_track.find(p);
	if (it != m_track.end()) {
		m_track.erase(it);
	}
}

void TrackerNew::dump() {
	for (auto it : m_track) {
		std::cout << "ox: " << it.first << "\t" << "file: " << it.second.file() << "\t" << "line: " << it.second.line() << std::endl;
	}
}

//#endif // !NDEBUG