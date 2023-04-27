package ru.covariance.controller;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.server.ResponseStatusException;
import reactor.core.publisher.Mono;
import ru.covariance.doc.User;
import ru.covariance.dto.RegisterUser;
import ru.covariance.repo.UserRepository;

@RestController
@RequestMapping("/user")
public class UserController {
    private final UserRepository userRepository;

    public UserController(UserRepository userRepository) {this.userRepository = userRepository;}

    @PostMapping
    public Mono<User> register(@RequestBody RegisterUser user) {
        User userToSave = new User();
        userToSave.setName(user.getName());
        try {
            userToSave.setCurrency(User.Currency.valueOf(user.getCurrency()));
        } catch (IllegalArgumentException e) {
            return Mono.error(() -> new ResponseStatusException(HttpStatus.BAD_REQUEST, "not supported currency"));
        }
        return userRepository.save(userToSave);
    }
}