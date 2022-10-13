from typing import Dict, List, Set
import numpy as np


class NaiveBayesClassifier():
    def __init__(self, k: int, lambdas: List[int], alpha: int):
        self.k = k
        self.lambdas = lambdas
        self.alpha = alpha

        self.counts: List[Dict[str, int]] = [{} for _ in range(k)]
        self.class_counts: List[int] = [0 for _ in range(k)]
        self.all_words: Set[str] = set()

        self.problems: List[Dict[str, int]] = [{} for _ in range(k)]
        self.n: int = 0


    def teach(self, c: int, words: List[str]):
        self.n += 1
        self.class_counts[c - 1] += 1
        for word in list(set(words)):
            self.all_words.add(word)
            self.counts[c - 1][word] = self.counts[c - 1].get(word, 0) + 1


    def fit(self):
        for i in range(self.k):
            for word, count in self.counts[i].items():
                self.problems[i][word] = (count + self.alpha) / (self.class_counts[i] + 2 * self.alpha)


    def predict(self, words: List[str]) -> List[float]:
        scores = [.0 for _ in range(self.k)]
        counter = 0
        sum = .0

        for i in range(self.k):
            if self.class_counts[i] != 0:
                score = np.log(lambdas[i] * self.class_counts[i] / self.n)

                for word in self.all_words:
                    v = self.problems[i].get(word, self.alpha / (self.class_counts[i] + 2 * self.alpha))
                    if word in words:
                        score += np.log(v)
                    else:
                        score += np.log(1 - v)

                scores[i] = score
                counter += 1
                sum += score

        avg = -sum / counter
        sum = .0

        for i in range(self.k):
            if self.class_counts[i] != 0:
                scores[i] = np.exp(avg + scores[i])
                sum += scores[i]

        return list(map(lambda x: x / sum, scores))


if __name__ == '__main__':
    k = int(input())
    lambdas = list(map(int, input().split()))
    alpha = int(input())
    N = int(input())

    bayes = NaiveBayesClassifier(k, lambdas, alpha)

    for _ in range(N):
        line = input().split()

        C = int(line[0])
        words = line[2:]

        bayes.teach(C, words)

    bayes.fit()

    M = int(input())
    for _ in range(M):
        words = input().split()[1:]

        print(' '.join(map('{:.10f}'.format, bayes.predict(words))))
