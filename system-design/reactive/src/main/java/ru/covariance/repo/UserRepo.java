package ru.covariance.repo;

import org.springframework.data.mongodb.repository.ReactiveMongoRepository;
import org.springframework.stereotype.Repository;
import ru.covariance.doc.User;

@Repository
public interface UserRepo extends ReactiveMongoRepository<User, String> {
}