package ru.covariance.vk_querier;

import com.vk.api.sdk.actions.Newsfeed;
import com.vk.api.sdk.client.VkApiClient;
import com.vk.api.sdk.client.actors.UserActor;
import com.vk.api.sdk.exceptions.ApiException;
import com.vk.api.sdk.exceptions.ClientException;
import com.vk.api.sdk.objects.newsfeed.responses.SearchResponse;
import com.vk.api.sdk.queries.newsfeed.NewsfeedSearchQuery;
import one.util.streamex.IntStreamEx;
import org.junit.Before;
import org.junit.Test;
import org.mockito.MockitoAnnotations;
import ru.covariance.vk_querier.querier.VkQuerier;
import ru.covariance.vk_querier.querier.VkQuerierImpl;

import java.util.Date;
import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.Matchers.*;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

@SuppressWarnings("FieldCanBeLocal")
public class VkQuerierTest {
  private Random random;
  private VkApiClient vkApiClient;
  private UserActor userActor;
  private VkQuerier vkRequester;

  @Before
  public void init() {
    MockitoAnnotations.initMocks(this);
    this.random = new Random();
    this.vkApiClient = mock(VkApiClient.class);
    this.userActor = mock(UserActor.class);
    this.vkRequester = new VkQuerierImpl(vkApiClient, userActor);
  }

  @Test
  public void testCount() throws ClientException, ApiException {
    final Newsfeed newsfeed = mock(Newsfeed.class);
    final NewsfeedSearchQuery newsfeedSearchQuery = mock(NewsfeedSearchQuery.class);
    final SearchResponse searchResponse = mock(SearchResponse.class);

    when(vkApiClient.newsfeed()).thenReturn(newsfeed);
    when(newsfeed.search(any(UserActor.class))).thenReturn(newsfeedSearchQuery);
    when(newsfeedSearchQuery.q(anyString())).thenReturn(newsfeedSearchQuery);
    when(newsfeedSearchQuery.count(anyInt())).thenReturn(newsfeedSearchQuery);
    when(newsfeedSearchQuery.startTime(anyInt())).thenReturn(newsfeedSearchQuery);
    when(newsfeedSearchQuery.endTime(anyInt())).thenReturn(newsfeedSearchQuery);
    when(newsfeedSearchQuery.startFrom(anyString())).thenReturn(newsfeedSearchQuery);
    when(newsfeedSearchQuery.execute()).thenReturn(searchResponse);

    for (int i = 0; i < 10; i++) {
      final int result = random.nextInt(1000);
      final AtomicInteger countedResult = new AtomicInteger(result);
      when(searchResponse.getNextFrom()).thenAnswer(invocation -> countedResult.get() > 200 ? "yes" : null);
      when(searchResponse.getItems()).thenAnswer(invocation -> {
        final int currentValue = Math.min(countedResult.get(), 200);
        countedResult.addAndGet(-200);
        return IntStreamEx.range(currentValue).boxed().toList();
      });
      assertThat(vkRequester.count("#what_happened", new Date(), new Date())).isEqualTo(result);
    }
  }
}