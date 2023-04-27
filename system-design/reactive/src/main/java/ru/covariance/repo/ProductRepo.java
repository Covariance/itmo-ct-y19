package ru.covariance.repo;

import org.springframework.data.mongodb.repository.ReactiveMongoRepository;
import org.springframework.stereotype.Repository;
import ru.covariance.doc.Product;

@Repository
public interface ProductRepo extends ReactiveMongoRepository<Product, String> {
}