import matplotlib.pyplot as plt
import numpy as np
import sklearn.neighbors
from sklearn import datasets
from sklearn import svm
from sklearn.metrics import accuracy_score, precision_score, recall_score
from sklearn.model_selection import train_test_split, StratifiedKFold, LeaveOneOut, cross_val_score
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier

########################################################################################################################
# 2 Manipulating a dataset
########################################################################################################################
from sklearn.svm import SVC


def getting_started():
    """
    + *k-fold* cross variation: the original sample is divided into k samples, one of the k samples is chosen as the
    validation set, the remaining k-1 are used to perform the training. This technique then gives us k performance
    scores, the standard deviation and the mean of these k data will then allow us to evaluate the network
    + *Leave-One-Out* cross-validation: this method is a variant of *k-fold* where k is 1. This means that each sample
    is compared with all the others, hence its name. This validation is more expensive than *k-fold* validation and most
    of the time leads to a high variance.
    + Cross validation *StratifiedKFold*: this method is a variation of the *k-fold* method, first *StratifiedKFold*
    mixes the data and cuts the data into k samples, the method therefore acts like *k-fold*, the samples are no longer
    blocks but spread out in the global dataset
    """
    iris = datasets.load_iris()
    X, y = iris.data, iris.target
    print(X.shape, y.shape)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25)
    clf = svm.SVC(kernel='linear', C=1).fit(X_train, y_train)
    score = clf.score(X_test, y_test)
    preds = clf.predict(X_test)
    print(preds)


########################################################################################################################
# 3 k nearest neighbour method
########################################################################################################################

def KNeighbors(percent, neighbors):
    """
    Perform an classification with percent of the data as test data and neighbors and return the score of each classed.
    """
    iris = datasets.load_iris()
    X, y = iris.data, iris.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=percent)
    clf = sklearn.neighbors.KNeighborsClassifier(n_neighbors=neighbors).fit(X_train, y_train)
    pred = clf.predict(X_test)
    accuracy = accuracy_score(y_test, pred)
    precision = precision_score(y_test, pred, average=None)
    recall = recall_score(y_test, pred, average=None)
    return accuracy, precision, recall


def rate_evolution():
    """
    Display the evolution of accuracy rate using KNeighbors with a neighbors from 1 to 9.
    Use MatPlotLib to draw accuracy_rate vs neighbors.
    """
    accuracy_rate = []
    for i in range(1, 10):
        accuracy, precision, recall = KNeighbors(0.5, i)
        accuracy_rate.append(accuracy)
        plt.plot(i, accuracy, 'r+')
    plt.xlabel('Number of neighbours')
    plt.ylabel('Accuracy rate')
    plt.title(
        'Evolution of the accuracy according to the number of neighbours \n of the KNeighborsClassifier classifier')
    print(accuracy_rate)
    plt.show()


def StratifiedKFoldUse(neighbors, method):
    """
    Perform a StratifeidKFold cross validation with K = 3 and return the accuracy_rate.
    """
    iris = datasets.load_iris()
    X, y = iris.data, iris.target
    skf = StratifiedKFold(n_splits=3)
    skf.get_n_splits(X, y)
    clf = sklearn.neighbors.KNeighborsClassifier(n_neighbors=neighbors, weights=method)
    cv = cross_val_score(clf, X, y, cv=skf)
    return cv


def rate_evolution_StratifiedKFold():
    """
    Display the evolution of accuracy rate using StratifiedKFold.
    Use MatPlotLib to draw accuracy_rate vs neighbors.
    """
    for i in range(1, 10):
        accuracy_rate_uniform = StratifiedKFoldUse(i, 'uniform')
        plt.plot(i, accuracy_rate_uniform[0], 'r+')
        plt.plot(i, accuracy_rate_uniform[1], 'g+')
        plt.plot(i, accuracy_rate_uniform[2], 'b+')
    plt.title(
        'Evolution of the accuracy according to the number \n of neighbours of the KNeighborsClassifier \n classifier using uniform weights and StratifiedKFold validation')
    plt.show()

    for i in range(1, 10):
        accuracy_rate_distance = StratifiedKFoldUse(i, 'distance')
        plt.plot(i, accuracy_rate_distance[0], 'bo')
        plt.plot(i, accuracy_rate_distance[1], 'go')
        plt.plot(i, accuracy_rate_distance[2], 'ro')
    plt.title(
        'Evolution of the accuracy according to the number \n of neighbours of the KNeighborsClassifier \n classifier using distance weights and StratifiedKFold validation')
    plt.show()


########################################################################################################################
# 4 Naive Bayesian Classifier
########################################################################################################################

def kNeighbours(neighbors):
    """
    Perform a classification with kNeighbours and return the accuracy_rate with wine dataset.
    """
    wine = datasets.load_wine()
    X, y = wine.data, wine.target
    skf = LeaveOneOut()
    skf.get_n_splits(X, y)
    clf = KNeighborsClassifier(neighbors, weights='uniform')
    cv = cross_val_score(clf, X, y, cv=skf)
    return cv.mean()


def baysian_classifier():
    """
    Perform a Naive bayesian classifier using leave ont out cross validation and wine dataset.
    """
    wine = datasets.load_wine()
    X, y = wine.data, wine.target
    skf = LeaveOneOut()
    skf.get_n_splits(X, y)
    clf = GaussianNB()
    cv = cross_val_score(clf, X, y, cv=skf)
    return cv.mean()


########################################################################################################################
# 5 Support vector machines
########################################################################################################################

def support_vector_machines(C, kernel):
    """
    Perform a SVM classification using SVC and fetch_olivetti_faces dataset
    """
    olivetti = datasets.fetch_olivetti_faces()
    X, y = olivetti.data, olivetti.target
    skf = StratifiedKFold(n_splits=3)
    skf.get_n_splits(X, y)
    clf = SVC(C=C, kernel=kernel)
    cv = cross_val_score(clf, X, y, cv=skf)
    return cv.mean()


def kNeighbours_faces(neighbors):
    """
    Perform a classification with kNeighbours and return the accuracy_rate with wine dataset.
    """
    olivetti = datasets.fetch_olivetti_faces()
    X, y = olivetti.data, olivetti.target
    skf = LeaveOneOut()
    skf.get_n_splits(X, y)
    clf = KNeighborsClassifier(neighbors, weights='uniform')
    cv = cross_val_score(clf, X, y, cv=skf)
    return cv.mean()


def baysian_classifier_faces():
    """
    Perform a Naive bayesian classifier using leave ont out cross validation and wine dataset.
    """
    olivetti = datasets.fetch_olivetti_faces()
    X, y = olivetti.data, olivetti.target
    skf = LeaveOneOut()
    skf.get_n_splits(X, y)
    clf = GaussianNB()
    cv = cross_val_score(clf, X, y, cv=skf)
    return cv.mean()


def display_SVM():
    x1, x2, x3, x4, y = [], [], [], [], []
    for i in range(1, 100):
        x1.append(support_vector_machines(i / 100, 'linear'))
        x2.append(support_vector_machines(i / 100, 'rbf'))
        y.append(i / 100)
    x3 = np.ones(len(x2)) * kNeighbours_faces(3)
    x4 = np.ones(len(x2)) * baysian_classifier_faces()
    plt.plot(y, x1, 'r+')
    plt.plot(y, x2, 'g+')
    plt.plot(y, x3, 'b+')
    plt.plot(y, x4, 'y+')
    plt.legend(['SVM linear', 'SVM rbf', 'kNeighbours (3 neighbours)', 'Bayesian'])
    plt.ylabel('Accuracy Rate')
    plt.xlabel('C')
    plt.title('Evolution of the accuracy according to the parameter C of the SVM classifier')
    plt.show()


# Looking at the figure SVM.png we can clearly see that the linear SVM classifier is the best as soon as
# C is large enough.
# The dataset can be considered as easy since we have a large amount of images per person (on average 10 images per person) which allows us to extract enough features to recognise each person. Moreover, each picture was taken at different times of the day and different orientations, allowing a large number of characteristics.
# For example, if 390 of the 400 photos were of the same person and 10 were of a different person, and our algorithm trained on the 390 similar images, validation on the other 10 images would have been catastrophic.

if __name__ == "__main__":
    getting_started()
    rate_evolution()
    rate_evolution_StratifiedKFold()
    print(StratifiedKFoldUse(3, 'uniform'))
    baye = baysian_classifier()
    neighbours = kNeighbours(3)
    print("Relative error %0.2f" % (abs(baye - neighbours) / baye))
    # display_SVM() #Warning : this function take time
