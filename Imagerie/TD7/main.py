"""
Réalisation du TD7 : Introduction au Deep Learning en vision par ordinateur
"""

########################################################################################################################
# 2. Chargement du jeu de données
########################################################################################################################
from keras import Sequential
from keras.applications.vgg16 import VGG16
from keras.layers import Dense, Conv2D, MaxPooling2D, Flatten
from keras.utils.np_utils import to_categorical
from matplotlib import pyplot as plt
from tensorflow.keras.datasets import mnist, cifar10


def display_images():
    """
    Affiche les 9 premières images de MNIST avec leurs classes associées
    """
    (X_train, y_train), (_, y_test) = mnist.load_data()
    for i in range(9):
        plt.subplot(331 + i)
        plt.imshow(X_train[i], cmap=plt.get_cmap('gray'))
        plt.title("Label : {}".format(y_train[i]))
    plt.show()


def load_one_hot():
    """
    Charge les données MNIST et convertit les labels au format one_hot
    :return les données chargées
    """
    (X_train, y_train), (X_test, y_test) = mnist.load_data()
    width, height, channels = X_train.shape[1], X_train.shape[2], 1
    X_train = X_train.reshape((X_train.shape[0], width * height))
    X_test = X_test.reshape((X_test.shape[0], width * height))
    X_train = X_train.astype('float32') / 255
    X_test = X_test.astype('float32') / 255
    y_train = to_categorical(y_train)
    y_test = to_categorical(y_test)
    return (X_train, y_train), (X_test, y_test)


########################################################################################################################
# 3 Réseaux de neurones à une seule couche
########################################################################################################################

def model_one_neuron():
    """
    Crée un réseau de neurones à une seule couche
    :return: le modèle créé
    """
    layer = Dense(units=10, activation='softmax', input_shape=(784,))
    model = Sequential(layer)
    model.compile(optimizer='sgd', loss='mae', metrics=['accuracy'])
    return model


def model_one_neuron_use():
    """
    Entraîne et utilise le réseau de neurones à une seule couche sur les données MNIST
    """
    model = model_one_neuron()
    (X_train, y_train), (_, y_test) = load_one_hot()
    history = model.fit(X_train, y_train, epochs=10, batch_size=32)
    # return model.evaluate(X_test, y_test)
    return history


def plot_loss_accuracy(title, history):
    accuracy, loss, x = [], [], []
    for i in range(len(history.history['accuracy'])):
        accuracy.append(history.history['accuracy'][i])
        loss.append(history.history['loss'][i])
        x.append(i)
    plt.plot(x, accuracy, label='accuracy')
    plt.plot(x, loss, label='loss')
    plt.legend()
    plt.xlabel('epoch')
    plt.title(title + '. Accuracy and Loss according to the number of epoch')
    plt.show()


########################################################################################################################
# 4. Réseau de neurones multi-couches
########################################################################################################################

def model_multi_layers(activation_1, activation_2, optimizer, loss):
    layer_1 = Dense(units=32, activation=activation_1, input_shape=(784,))
    model = Sequential(layer_1)
    layer_2 = Dense(units=10, activation=activation_2)
    model.add(layer_2)
    model.compile(optimizer=optimizer, loss=loss, metrics=['accuracy'])
    return model


def model_multi_layers_use():
    (X_train, y_train), (_, y_test) = load_one_hot()
    model_1 = model_multi_layers('relu', 'softmax', 'sgd', 'mae')
    model_2 = model_multi_layers('sigmoid', 'softmax', 'sgd', 'mae')
    model_3 = model_multi_layers('relu', 'softmax', 'adam', 'mae')
    model_4 = model_multi_layers('relu', 'softmax', 'sgd', 'categorical_crossentropy')
    history_1 = model_1.fit(X_train, y_train, epochs=10, batch_size=32)
    history_2 = model_2.fit(X_train, y_train, epochs=10, batch_size=32)
    history_3 = model_3.fit(X_train, y_train, epochs=10, batch_size=32)
    history_4 = model_4.fit(X_train, y_train, epochs=10, batch_size=32)
    return history_1, history_2, history_3, history_4


def plot_multi_layers_use(history):
    history_1, history_2, history_3, history_4 = history
    accuracy, loss, x = [], [], []
    for i in range(len(history_1.history['accuracy'])):
        accuracy.append(history_1.history['accuracy'][i])
        loss.append(history_1.history['loss'][i])
        x.append(i)
    plt.plot(x, accuracy, label='1. accuracy')
    plt.plot(x, loss, label='1. loss')

    accuracy, loss, x = [], [], []
    for i in range(len(history_2.history['accuracy'])):
        accuracy.append(history_2.history['accuracy'][i])
        loss.append(history_2.history['loss'][i])
        x.append(i)
    plt.plot(x, accuracy, label='2. (sigmoid) accuracy')
    plt.plot(x, loss, label='2. (sigmoid) loss')

    accuracy, loss, x = [], [], []
    for i in range(len(history_3.history['accuracy'])):
        accuracy.append(history_3.history['accuracy'][i])
        loss.append(history_3.history['loss'][i])
        x.append(i)
    plt.plot(x, accuracy, label='3. (adam) accuracy')
    plt.plot(x, loss, label='3. (adam) loss')

    accuracy, loss, x = [], [], []
    for i in range(len(history_4.history['accuracy'])):
        accuracy.append(history_4.history['accuracy'][i])
        loss.append(history_4.history['loss'][i])
        x.append(i)
    plt.plot(x, accuracy, label='4. (categorical_crossentropy) accuracy')
    plt.plot(x, loss, label='4. (categorical_crossentropy) loss')
    plt.legend()
    plt.title('Multi Layers \n Accuracy and Loss according to the number of epoch and different methods')
    plt.xlabel('epoch')
    plt.show()


########################################################################################################################
# 5. Réseaux de neurones convolutionnels
########################################################################################################################

def load_2D_data():
    (X_train, y_train), (X_test, y_test) = mnist.load_data()
    width, height, channels = X_train.shape[1], X_train.shape[2], 1
    X_train = X_train.reshape((X_train.shape[0], width, height, 1))
    X_test = X_test.reshape((X_test.shape[0], width, height, 1))
    X_train = X_train.astype('float32') / 255
    X_test = X_test.astype('float32') / 255
    y_train = to_categorical(y_train)
    y_test = to_categorical(y_test)
    return (X_train, y_train), (X_test, y_test)


def model_convolution():
    model = Sequential([
        Conv2D(8, kernel_size=(5, 5), activation='relu', input_shape=(28, 28, 1)),  # paramètres h*w*8
        MaxPooling2D(),
        Conv2D(16, kernel_size=(5, 5), activation='relu'),  # 5*5*8*16
        MaxPooling2D(),
        Flatten(),
        Dense(128, activation='relu'),
        Dense(64, activation='relu'),
        Dense(10, activation='softmax')
    ])
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    return model


def model_convolution_use():
    model = model_convolution()
    (X_train, y_train), (_, y_test) = load_2D_data()
    history = model.fit(X_train, y_train, epochs=10, batch_size=32)
    for layer in model.layers:
        weights = layer.get_weights()
        print(weights)
    return history


########################################################################################################################
# 6. Réutilisation de modèles existants
########################################################################################################################

def VGG16_use():
    model = VGG16(
        include_top=False,
        input_shape=(32, 32, 3)
    )
    print(model.summary())
    (X_train, y_train), (X_test, y_test) = cifar10.load_data()
    result = model.predict(X_test)
    print(result)


if __name__ == "__main__":
    display_images()
    plot_loss_accuracy("One Layer", model_one_neuron_use())
    plot_multi_layers_use(model_multi_layers_use())
    plot_loss_accuracy("Convolution model", model_convolution_use()) # La diminution des filtres pour les couches de convolution entraine une loss plus élevée et une accuracy légèrement plus faible
    VGG16_use()
