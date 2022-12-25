package statistics

import (
	"clock/pkg/clock"
	"github.com/gammazero/deque"
	"log"
	"time"
)

type EventsStatistics interface {
	IncEvent(name string)
	GetEventStatisticByName(name string) int
	GetAllEventStatistic() map[string]int
	PrintStatistic()
}

type event struct {
	time  time.Time
	event string
}

type eventStatisticsImpl struct {
	deq         *deque.Deque[event]
	counter     map[string]int
	clock       clock.Clock
	granularity time.Duration
}

func (r *eventStatisticsImpl) clearOldEvents() {
	now := r.clock.Now()

	for r.deq.Len() != 0 && now.Sub(r.deq.Front().time) >= r.granularity {
		oldestEvent := r.deq.PopFront().event

		r.counter[oldestEvent] -= 1

		if r.counter[oldestEvent] == 0 {
			delete(r.counter, oldestEvent)
		}
	}
}

func (r *eventStatisticsImpl) IncEvent(name string) {
	r.clearOldEvents()

	r.deq.PushBack(event{
		time:  r.clock.Now(),
		event: name,
	})

	r.counter[name] += 1
}

func (r *eventStatisticsImpl) GetEventStatisticByName(name string) int {
	r.clearOldEvents()

	return r.counter[name]
}

func (r *eventStatisticsImpl) GetAllEventStatistic() map[string]int {
	r.clearOldEvents()

	return r.counter
}

func (r *eventStatisticsImpl) PrintStatistic() {
	r.clearOldEvents()

	for k, v := range r.counter {
		log.Printf("%s: %d, %.2f [rpm]\n", k, v, float64(v)/r.granularity.Minutes())
	}
}

func NewEventsStatistics(clock clock.Clock, granularity time.Duration) EventsStatistics {
	return &eventStatisticsImpl{
		deq:         deque.New[event](0),
		counter:     map[string]int{},
		clock:       clock,
		granularity: granularity,
	}
}
