package ru.covariance.vk_querier.counter;

import lombok.RequiredArgsConstructor;
import one.util.streamex.IntStreamEx;
import ru.covariance.vk_querier.querier.VkQuerier;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.chrono.ChronoZonedDateTime;
import java.util.Date;

@RequiredArgsConstructor
public class FrequencyCounterImpl implements FrequencyCounter {
  private final VkQuerier querier;

  @Override
  public int[] count(final String hashTag, final int hours) {
    if (hours < 1 || hours > 24) {
      throw new IllegalArgumentException("Number of hours should be in range from 1 to 24");
    }

    final LocalDateTime currentDate = LocalDateTime.now();
    return IntStreamEx.range(hours + 1).boxed()
        .map(currentDate::minusHours)
        .map(date -> date.atZone(ZoneId.systemDefault()))
        .map(ChronoZonedDateTime::toInstant)
        .map(Date::from)
        .pairMap((endDate, startDate) -> querier.count(hashTag, startDate, endDate))
        .mapToInt(x -> x)
        .toArray();
  }
}
