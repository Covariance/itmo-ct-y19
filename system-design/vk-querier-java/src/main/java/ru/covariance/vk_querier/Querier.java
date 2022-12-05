package ru.covariance.vk_querier.querier;

import java.util.Date;

public interface VkQuerier {
  int count(final String key, final Date startTime, final Date endTime);
}
