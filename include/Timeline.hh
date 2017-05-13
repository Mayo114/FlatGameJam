//
// Timeline.hh for FlatGameJam in /home/boulag_l/rendu/FlatGameJam/include
//
// Made by Luka Boulagnon
// Login   <luka.boulagnon@epitech.eu@epitech.net>
//
// Started on  sam. mai 13 18:56:08 2017 Luka Boulagnon
// Last update sam. mai 13 18:56:08 2017 Luka Boulagnon
//

#ifndef TIMELINE_HH
#define TIMELINE_HH

#include <map>

class Event {
 public:
  enum EventType { KILLED, FOUGHT, LETALIVE, ALLIANCE, DISCUSS };
  Event(EventType);

 private:
  EventType type;
};

class Timeline {
 public:
  Timeline();
  void addEvent(double, Event);
  std::map<double, Event>::const_iterator each() const;

 private:
  std::map<double, Event> events;
};

#endif /* !TIMELINE_HH */
