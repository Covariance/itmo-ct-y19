package statistics

import (
	"bytes"
	"clock/pkg/clock"
	"github.com/stretchr/testify/assert"
	"log"
	"os"
	"testing"
	"time"
)

func setup(t *testing.T, granularity time.Duration) (time.Time, *clock.FakeClock, EventsStatistics) {
	t.Helper()

	cl := clock.NewFakeClock()
	tm := cl.Now()
	es := NewEventsStatistics(cl, granularity)

	return tm, cl, es
}

func captureOutput(t *testing.T, f func()) string {
	t.Helper()

	var buf bytes.Buffer
	log.SetOutput(&buf)
	f()
	log.SetOutput(os.Stderr)
	return buf.String()
}

func TestIncrement(t *testing.T) {
	_, _, es := setup(t, time.Hour)

	es.IncEvent("a")
	assert.Equal(t, 1, es.GetEventStatisticByName("a"))

	es.IncEvent("a")
	assert.Equal(t, 2, es.GetEventStatisticByName("a"))
}

func TestOldEventErasure(t *testing.T) {
	_, cl, es := setup(t, time.Minute)

	es.IncEvent("a")
	assert.Equal(t, 1, es.GetEventStatisticByName("a"))

	cl.Elapse(2 * time.Minute)
	assert.Equal(t, 0, es.GetEventStatisticByName("a"))
}

func TestSeriesOfIncrements(t *testing.T) {
	_, cl, es := setup(t, time.Minute)

	es.IncEvent("a")
	assert.Equal(t, 1, es.GetEventStatisticByName("a"))

	cl.Elapse(31 * time.Second)
	es.IncEvent("a")
	assert.Equal(t, 2, es.GetEventStatisticByName("a"))

	cl.Elapse(31 * time.Second)
	assert.Equal(t, 1, es.GetEventStatisticByName("a"))

	cl.Elapse(31 * time.Second)
	assert.Equal(t, 0, es.GetEventStatisticByName("a"))
}

func TestAllStatistics(t *testing.T) {
	_, _, es := setup(t, time.Minute)

	es.IncEvent("a")
	es.IncEvent("a")
	es.IncEvent("a")

	es.IncEvent("b")
	es.IncEvent("b")

	es.IncEvent("c")

	assert.Equal(t, map[string]int{"a": 3, "b": 2, "c": 1}, es.GetAllEventStatistic())
}
