from __future__ import print_function
from pygarl.base import CallbackManager
from pygarl.classifiers import SVMClassifier
from pygarl.mocks import VerboseMiddleware
from pygarl.data_readers import SerialDataReader
from pygarl.predictors import ClassifierPredictor
from pygarl.sample_managers import DiscreteSampleManager

MODEL_PATH="C:\\Users\\Admin\\model.svm"
PORT="COM4"

def receive_character(letter):
    print(letter)


sdr = SerialDataReader(PORT, expected_axis=6, verbose=False)

manager = DiscreteSampleManager()

sdr.attach_manager(manager)

classifier = SVMClassifier(model_path=MODEL_PATH)

classifier.load()

classifier.print_info()

predictor = ClassifierPredictor(classifier)

manager.attach_receiver(predictor)

callback_mg = CallbackManager(verbose=True)

predictor.attach_callback_manager(callback_mg)

for c in ["a", "b", "c", "d","e"]:
    callback_mg.attach_callback(c, receive_character)

sdr.open()
print("Opened!")

sdr.mainloop()
