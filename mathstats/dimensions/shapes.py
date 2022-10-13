from abc import ABC, abstractmethod
from matplotlib import pyplot as plt
from matplotlib.collections import LineCollection
import numpy as np
from typing import List, Tuple
from math import pi
from imageio import imread


class Shape(ABC):
    @abstractmethod
    def __init__(self):
        pass
    
    @abstractmethod
    def does_intersect(self, x: float, y: float, eps: float) -> bool:
        pass
    
    @abstractmethod
    def show(self, ax: plt.Axes):
        pass

class Circle(Shape):
    def __init__(self, x: float = 1 / 2, y: float = 1 / 2, rad: float = 1 / 2):
        self.center_ = np.array((x, y))
        self.radius_ = rad
    
    def does_intersect(self, x: float, y: float, eps: float) -> bool:
        point = np.array((x, y))
        
        return np.linalg.norm(point - self.center_) < self.radius_ + eps
    
    def show(self, ax: plt.Axes):
        ring = plt.Circle(self.center_, self.radius_)
        ax.add_patch(ring)
        ax.set_xticks([])
        ax.set_yticks([])
        ax.spines['right'].set_visible(False)
        ax.spines['left'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.spines['bottom'].set_visible(False)
        ax.set_xlim((
            self.center_[0] - self.radius_ - .1,
            self.center_[1] + self.radius_ + .1
        ))
        ax.set_ylim((
            self.center_[0] - self.radius_ - .1,
            self.center_[1] + self.radius_ + .1
        ))

class Ring(Shape):
    def __init__(self, x: float = 1 / 2, y: float = 1 / 2, rad: float = 1 / 2):
        self.center_ = np.array((x, y))
        self.radius_ = rad
    
    def does_intersect(self, x: float, y: float, eps: float) -> bool:
        point = np.array((x, y))
        
        return np.abs(np.linalg.norm(point - self.center_) - self.radius_) < eps
    
    def show(self, ax: plt.Axes):
        ring = plt.Circle(self.center_, self.radius_, fill = False)
        ax.add_patch(ring)
        ax.set_xticks([])
        ax.set_yticks([])
        ax.spines['right'].set_visible(False)
        ax.spines['left'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.spines['bottom'].set_visible(False)
        ax.set_xlim((
            self.center_[0] - self.radius_ - .1,
            self.center_[1] + self.radius_ + .1
        ))
        ax.set_ylim((
            self.center_[0] - self.radius_ - .1,
            self.center_[1] + self.radius_ + .1
        ))

class KochSnoflake(Shape):
    SIXTY = np.array((
        (np.cos(pi / 3), -np.sin(pi / 3)),
        (np.sin(pi / 3), np.cos(pi / 3))
    ))
    
    def __init__(self, depth: int = 5):
        initlines = [
            (np.array([1 / 2 - np.sqrt(3) / 4, 1 / 4]), np.array([1 / 2, 1.])),
            (np.array([1 / 2, 1.]), np.array([1 / 2 + np.sqrt(3) / 4, 1 / 4])),
            (np.array([1 / 2 + np.sqrt(3) / 4, 1 / 4]), np.array([1 / 2 - np.sqrt(3) / 4, 1 / 4]))
        ]
        self.reslines_ = KochSnoflake.__build(initlines, depth - 1)
        
    def __build(lines: List[Tuple[np.ndarray]], depth: int) -> List[Tuple[np.ndarray]]:
        if depth == 0:
            return lines
        
        outlines : List[Tuple[np.ndarray]] = []
        
        for line in lines:
            first = line[0]
            fourth = line[1]
            second = (2 * first + fourth) / 3
            third = (first + 2 * fourth) / 3
            
            # Adding the triangle
            spike = KochSnoflake.SIXTY.dot(second - first) + second
            
            outlines.append((second, spike))
            outlines.append((spike, third))
            
            # Adding remaining segments
            outlines.append((first, second))
            outlines.append((third, fourth))
            
        return KochSnoflake.__build(outlines, depth - 1)
    
    
    def does_intersect(self, x: float, y: float, eps: float) -> bool:
        point = np.array([x, y])
        
        for line in self.reslines_:
            dir = line[1] - line[0]
            
            angle_a = dir.dot(point - line[0])
            angle_b = (-dir).dot(point - line[1])
            
            if angle_a < 0. or angle_b < 0.:
                continue
            
            if np.linalg.norm(np.cross(point - line[0], dir)) / np.linalg.norm(dir) < eps:
                return True
            
        return False
    
    
    def show(self, ax: plt.Axes):
        col = LineCollection(self.reslines_)
        ax.add_collection(col)
        ax.set_xticks([])
        ax.set_yticks([])
        ax.spines['right'].set_visible(False)
        ax.spines['left'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.spines['bottom'].set_visible(False)


class CantorSet(Shape):
    def __init__(self, depth: int = 10, height: float = 0.):
        self.height_ = height
        initlines = [
            (np.array([0., self.height_]), np.array([1., self.height_]))
        ]
        self.reslines_ = CantorSet.__build(initlines, depth-1)
    
    def __build(lines: List[Tuple[np.ndarray]], depth: int) -> List[Tuple[np.ndarray]]:
        if depth == 0:
            return lines
        
        outlines : List[Tuple[np.ndarray]] = []
        
        for line in lines:
            outlines.append((line[0], (2 * line[0] + line[1]) / 3))
            outlines.append(((line[0] + 2 * line[1]) / 3, line[1]))
            
        return CantorSet.__build(outlines, depth - 1)
    
    def does_intersect(self, x: float, y: float, eps: float) -> bool:
        if not (0. <= x <= 1.):
            return False
        
        if np.abs(y - self.height_) > eps:
            return False
        
        shift = np.sqrt(eps ** 2 - (y - self.height_) ** 2)
        seg_left, seg_right = x - shift, x + shift
        
        # We would perform the check via trinary form of the number
        # If it contains any 1s, number is out
        left, right = 0., 1.
        
        while True:
            second, third = (2 * left + right) / 3, (left + 2 * right) / 3
            # Check where the borders of seg land
            if seg_left <= second <= seg_right or seg_left <= third <= seg_right:
                return True
            
            if second <= seg_left and seg_right <= third:
                return False
            
            if seg_right <= second:
                right = second
            else:
                left = third

    
    def show(self, ax: plt.Axes):
        col = LineCollection(self.reslines_, linewidths=3)
        ax.add_collection(col)
        ax.set_xticks([])
        ax.set_yticks([])
        ax.spines['right'].set_visible(False)
        ax.spines['left'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.spines['bottom'].set_visible(False)
        ax.set_xlim((-.1, 1.1))
        ax.set_ylim((self.height_ - .6, self.height_ + .6))

class ImageShape(Shape):
    def __init__(self, image: str):
        self.img_ = imread(image)
        self.size_ = self.img_.shape[0]

    def does_intersect(self, x: float, y: float, eps: float) -> bool:
        xborder = (max(0., x - eps), min(1., x + eps))
        yborder = (max(0., y - eps), min(1., y + eps))
        
        xfrom, xto = int(xborder[0] * self.size_), int(xborder[1] * self.size_)
        yfrom, yto = int(yborder[0] * self.size_), int(yborder[1] * self.size_)
    
        for xc in range(xfrom, xto):
            for yc in range(yfrom, yto):
                if self.img_[xc][yc].mean() < 127:
                    return True
        
        return False 
    
    def show(self, ax: plt.Axes):
        ax.imshow(self.img_, interpolation='nearest')
        ax.set_xticks([])
        ax.set_yticks([])
        ax.spines['right'].set_visible(False)
        ax.spines['left'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.spines['bottom'].set_visible(False)
