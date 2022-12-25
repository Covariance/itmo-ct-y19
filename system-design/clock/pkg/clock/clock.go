package clock

import "time"

type Clock interface {
	Now() time.Time
}

type RealClock struct{}

func (r *RealClock) Now() time.Time {
	return time.Now()
}

func NewRealClock() *RealClock {
	return &RealClock{}
}

type FakeClock struct {
	now time.Time
}

func NewFakeClock() *FakeClock {
	return &FakeClock{now: time.Now()}
}

func NewFakeClockSet(time time.Time) *FakeClock {
	return &FakeClock{now: time}
}

func (r *FakeClock) Now() time.Time {
	return r.now
}

func (r *FakeClock) Elapse(duration time.Duration) {
	r.now = r.now.Add(duration)
}

func (r *FakeClock) Set(time time.Time) {
	r.now = time
}
