package ru.covariance.vk_querier.counter;

public interface FrequencyCounter {
  int[] count(final String hashTag, final int hours);
}
