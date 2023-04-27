package ru.covariance.controller;

import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;
import ru.covariance.doc.Product;
import ru.covariance.doc.User;
import ru.covariance.dto.AddProductRequest;
import ru.covariance.repo.ProductRepository;
import ru.covariance.repo.UserRepository;

@RestController
@RequestMapping("/shop")
public class ShopController {
    private final ProductRepository productRepository;
    private final UserRepository userRepository;

    public ShopController(ProductRepository productRepository, UserRepository userRepository) {
        this.productRepository = productRepository;
        this.userRepository = userRepository;
    }

    @PostMapping
    public Mono<Product> addProduct(@RequestBody AddProductRequest product) {
        Product productToSave = new Product();
        productToSave.setName(product.getName());
        productToSave.setPrice(product.getPrice());
        return productRepository.save(productToSave);
    }

    @GetMapping(value = "/{user_id}")
    public Flux<Product> getAllProduct(@PathVariable(value = "user_id") String userId) {
        Mono<User> user = userRepository.findById(userId);
        Flux<Product> products = productRepository.findAll();
        return products.flatMap(product -> user.map(u -> switch (u.getCurrency()) {
            case RUB -> product;
            case USD -> product.withPrice(product.getPrice() * 80);
            case EUR -> product.withPrice(product.getPrice() * 90);
        }));
    }
}