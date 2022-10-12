#!/usr/bin/env python

""" 
Developers: DSOR Team -> @tecnico.ulisboa.pt Instituto Superior Tecnico
"""
import rospy
from python_counter_algorithms.PythonCounterAlgorithm import count_function
from std_msgs.msg import Int32, Bool

class PythonCounterNode():
    def __init__(self):
        """
        Constructor for ros node
        """

        """
        @.@ Init node
        """
        rospy.init_node('python_counter_node')

        
        """
        @.@ Handy Variables
        # Declare here some variables you might think usefull -> example: self.fiic = true
        """

        

        """
        @.@ Dirty work of declaring subscribers, publishers and load parameters 
        """
        self.loadParams()
        self.initializeSubscribers()
        self.initializePublishers()
        self.initializeTimer()
        #self.initializeServices()

        

    """
    @.@ Member Helper function to set up parameters; 
    """
    def loadParams(self):
        self.node_frequency = rospy.get_param('~node_frequency')
        # rospy.loginfo('node_frequency acquired: ' + str(self.node_frequency))
        self.num = rospy.get_param('~start_num')
        self.pause = False


    """
    @.@ Member Helper function to set up subscribers; 
    """
    def initializeSubscribers(self):
        rospy.loginfo('Initializing Subscribers for PythonCounterNode')
        rospy.Subscriber(rospy.get_param('~topics/subscribers/pause'), Bool, self.set_pause)
    
    """
    @.@ Member Helper function to set up publishers; 
    """
    def initializePublishers(self):
        rospy.loginfo('Initializing Publishers for PythonCounterNode')
        self.pub_count = rospy.Publisher(rospy.get_param('~topics/publishers/count'), Int32, queue_size=10)

    """
    @.@ Member helper function to set up the timer
    """
    def initializeTimer(self):
        self.timer = rospy.Timer(rospy.Duration(1.0/self.node_frequency),self.timerIterCallback)


    """
    @.@ Member helper function to shutdown timer;
    """
    def shutdownTimer(self):
        self.timer.shutdown()


    """
    @.@ Timer iter callback. Where the magic should happen
    """
    def timerIterCallback(self, event=None):
        if not self.pause:
            self.num = count_function(self.num)
        self.pub_count.publish(self.num)


    def set_pause(self, data):
        self.pause = data.data



def main():

    python_counter = PythonCounterNode()

    # +.+ Going into spin; let the callbacks do all the magic 
    rospy.spin()

if __name__ == '__main__':
    main()
