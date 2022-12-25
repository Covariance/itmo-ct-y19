package clock

import (
	"testing"
	"time"

	"github.com/stretchr/testify/require"
)

func TestFakeClock(t *testing.T) {
	now := time.Now()
	clock := NewFakeClockSet(now)
	duration := 10 * time.Minute

	clock.Elapse(duration)

	require.Equal(t, now.Add(duration), clock.Now())
}
