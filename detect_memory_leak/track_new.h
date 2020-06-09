#ifndef TRACK_NEW_H
#define TRACK_NEW_H

//#ifndef NDEBUG

#include <map>

void* operator new(size_t size, const char *file, long line);
void* operator new(size_t size);
void operator delete(void *p);

class TrackerNew {
	class TrackerNewIn {
		const char *m_file;
		long m_line;
	public:
		TrackerNewIn(const char *file = nullptr, long line = 0) :m_file(file), m_line(line){ }
		~TrackerNewIn(){ }
		const char *file() const { return m_file; }
		long line() const { return m_line; }
	};
	class Lock {		//ʡȥm_lock_cout���Լ����������
		TrackerNew &_track;
	public:
		Lock(TrackerNew &track) :_track(track) {
			_track.m_lock_count++;
		}
		~Lock() {
			_track.m_lock_count--;
		}
	};

public:
	TrackerNew();
	~TrackerNew();
	void add(void *p, const char *file, long line);
	void remove(void *p);
	void dump();
public:
	static bool flag;
private:
	std::map<void*, TrackerNewIn> m_track;
	long m_lock_count; //Ϊ�˱������޵���
};

extern TrackerNew tracker_new;

//#endif // !NDEBUG

#endif TRACK_NEW_H //!TRACK_NEW_H