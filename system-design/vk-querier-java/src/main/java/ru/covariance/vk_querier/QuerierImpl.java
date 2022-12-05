package ru.covariance.vk_querier.querier;
import com.vk.api.sdk.client.VkApiClient;
import com.vk.api.sdk.client.actors.UserActor;
import com.vk.api.sdk.objects.newsfeed.responses.SearchResponse;
import com.vk.api.sdk.exceptions.ApiException;
import com.vk.api.sdk.exceptions.ClientException;
import lombok.RequiredArgsConstructor;
import org.apache.logging.log4j.util.Strings;

import java.util.Date;

@RequiredArgsConstructor
public class VkQuerierImpl implements VkQuerier {
    private final VkApiClient vkApiClient;
    private final UserActor userActor;

    @Override
    public int count(String key, Date startDate, Date endDate) {
      try {
        int result = 0;
        String startFrom = "";
        do {
          final SearchResponse searchResponse = vkApiClient.newsfeed()
              .search(userActor)
              .q(key)
              .count(200)
              .startTime((int) startDate.toInstant().getEpochSecond())
              .endTime((int) endDate.toInstant().getEpochSecond())
              .startFrom(startFrom)
              .execute();
          startFrom = searchResponse.getNextFrom();
          result += searchResponse.getItems().size();
        } while (!Strings.isEmpty(startFrom));
        return result;
      } catch (ApiException | ClientException e) {
        throw new RuntimeException("Problems with connection to vk.", e);
      }
    }

}
