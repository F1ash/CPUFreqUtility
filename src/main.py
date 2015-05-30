# -*- coding: utf-8 -*-

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyKDE4.kdecore import KAuth, KGlobal
from PyKDE4.plasma import Plasma
from PyKDE4 import plasmascript
import os.path, os

def readCpuData(number, fileName):
	args = {}
	args["procnumb"] = QString(number)
	args["filename"] = QString(fileName)

	act = KAuth.Action('org.freedesktop.auth.cpufrequtility.read')
	act.setHelperID('org.freedesktop.auth.cpufrequtility')
	act.setArguments(args)
	#print act.hasHelper(), 'ready', act.helperID(), act.name(), 'Valid is', act.isValid()
	reply = act.execute()
	if (reply.failed()) :
		QMessageBox.information(None, "Error", \
					QString("KAuth returned an error code: %1 \n %2").arg(reply.errorCode()).arg(reply.errorDescription()))
		reply.setData(QVariant({QString('contents') : 0}).toMap())
		#print [reply.data()]
	else :
		#print reply.data(), 'reply from :', act.hasHelper(), act.name(), 'Valid is', act.isValid()
		pass
	return reply

def writeCpuData(number, fileName, parametr):
	args = {}
	args["procnumb"] = number
	args["filename"] = fileName
	args["parametr"] = parametr

	act = KAuth.Action('org.freedesktop.auth.cpufrequtility.write')
	act.setHelperID('org.freedesktop.auth.cpufrequtility')
	act.setArguments(args)
	reply = act.execute()
	if (reply.failed()) :
		QMessageBox.information(None, "Error", \
					QString("KAuth returned an error code: %1 \n %2").arg(reply.errorCode()).arg(reply.errorDescription()))
	else :
		#print reply.data(), 'reply from :', act.hasHelper(), act.name(), 'Valid is', act.isValid()
		pass
	return reply

"""
/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_frequencies
		contents available freq* (2001 2000 1600 1200 800)
/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_governors
		contents available governor regimes
/sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
		for change regime
/sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq
		current freq (for ex.: 800)
/sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq
		current max freq
/sys/devices/system/cpu/cpu*/cpufreq/scaling_min_freq
		current min freq
/sys/devices/system/cpu/cpu*/online
		enable\disable(1\0) proc, not for cpu0
/sys/devices/system/cpu/possible
		check possible proc (for ex.: 0-1)
/sys/devices/system/cpu/present
		check present proc (for ex.: 0-1)
"""

def define_proc_data():
	COUNT_PROCESSOR = os.sysconf('SC_NPROCESSORS_ONLN')
	procData = {}
	_count = readCpuData('null', 'possible')
	count = _count.data()[QString('contents')].toString().replace('\n', '').split('-')
	_present = readCpuData('null', 'present')
	present = _present.data()[QString('contents')].toString().replace('\n', '').split('-')
	#print len(count), COUNT_PROCESSOR, ":", [str(present[i]) for i in xrange(len(present))]
	global COUNT_PROC
	if _count.failed() or _present.failed() :
		COUNT_PROC = 0
		procData['count'] = COUNT_PROC
		return procData
	COUNT_PROC = max(COUNT_PROCESSOR, len(count))
	procData['count'] = COUNT_PROC
	procData['availableFreqs'] = {int(i) : readCpuData(str(i), 'available_frequencies') for i in xrange(COUNT_PROC)}
	#print [procData['availableFreqs'][i].data()[QString('contents')].toString() for i in xrange(COUNT_PROC)]
	procData['availableGovernors'] = {int(i) : readCpuData(str(i), 'available_governors') for i in xrange(COUNT_PROC)}
	#print [procData['availableGovernors'][i].data()[QString('contents')].toString() for i in xrange(COUNT_PROC)]
	procData['currentFreq'] = {int(i) : readCpuData(str(i), 'cur_freq') for i in xrange(COUNT_PROC)}
	#print [procData['currentFreq'][i].data()[QString('contents')].toString() for i in xrange(COUNT_PROC)]
	procData['currentGovernor'] = {int(i) : readCpuData(str(i), 'governor') for i in xrange(COUNT_PROC)}
	#print [procData['currentGovernor'][i].data()[QString('contents')].toString() for i in xrange(COUNT_PROC)]
	procData['currentMaxFreq'] = {int(i) : readCpuData(str(i), 'max_freq') for i in xrange(COUNT_PROC)}
	#print [procData['currentMaxFreq'][i].data()[QString('contents')].toString() for i in xrange(COUNT_PROC)]
	procData['currentMinFreq'] = {int(i) : readCpuData(str(i), 'min_freq') for i in xrange(COUNT_PROC)}
	#print [procData['currentMinFreq'][i].data()[QString('contents')].toString() for i in xrange(COUNT_PROC)]
	""" WARNING : /sys/devices/system/cpu/cpu0/online not exist anyway """
	procData['online'] = {int(i) : readCpuData(str(i), 'online') for i in xrange(COUNT_PROC)}
	#print [(i, procData['online'][int(i)].data()[QString('contents')].toString()) for i in xrange(COUNT_PROC)]
	return procData

class plasmaCpuFreqUtility(plasmascript.Applet):
	def __init__(self, parent = None):
		plasmascript.Applet.__init__(self, parent)

		self.kdehome = unicode(KGlobal.dirs().localkdedir())

		if os.path.exists('/usr/share/kde4/apps/plasma/plasmoids/kde-plasma-cpufrequtility/contents/icons/performance.png') :
			self.iconPath = '/usr/share/kde4/apps/plasma/plasmoids/kde-plasma-cpufrequtility/contents/icons/performance.png'
		elif os.path.exists(self.kdehome + '/share/apps/plasma/plasmoids/kde-plasma-cpufrequtility/contents/icons/performance.png') :
			self.iconPath = self.kdehome + '/share/apps/plasma/plasmoids/kde-plasma-cpufrequtility/contents/icons/performance.png'
			#print 'installing', self.iconPath
		else :
			self.iconPath = os.getcwd() + '/plasmaCpuFreqUtility/contents/icons/performance.png'

		self.Settings = QSettings('kde-plasma-cpufrequtility', 'kde-plasma-cpufrequtility')

	def init(self):
		self.setImmutability(Plasma.Mutable)
		self.setHasConfigurationInterface(False)
		self.layout = QGraphicsLinearLayout(self.applet)
		self.layout.setSpacing(0)
		self.icon = Plasma.IconWidget()
		self.icon.setIcon(self.iconPath)
		self.icon.setMinimumIconSize(QSizeF(24.0, 24.0))
		self.icon.clicked.connect(self.mouseDoubleClickEvent)
		self.layout.addItem(self.icon)
		self.setLayout(self.layout)

		self.ProcData = define_proc_data()
		self.Control = ControlWidget(self.ProcData, self, os.path.dirname(self.iconPath))

	def mouseDoubleClickEvent(self, ev = True):
		if type(ev) is not bool : ev.ignore()
		if self.Control.isVisible() :
			self.Control.hide()
		else:
			self.Control.show()
			self.Control.move(self.popupPosition(self.Control.size()))

	def parametersReset(self):
		self.ProcData = define_proc_data()

	def getLastProcParemeters(self):
		lastParameters = {}
		i = 0
		for paramProc in self.Settings.value('Parameters', '').toString().split(";;", QString.SkipEmptyParts) :
			lastParameters[i] = {}
			parameters = paramProc.split(" ", QString.SkipEmptyParts)
			lastParameters[i]['regime'] = str(parameters[1])
			lastParameters[i]['minfrq'] = str(parameters[2])
			lastParameters[i]['maxfrq'] = str(parameters[3])
			i += 1
		return lastParameters

class ControlWidget(Plasma.Dialog):
	def __init__(self, procData, obj, iconDir, parent = None):
		Plasma.Dialog.__init__(self, parent)
		self.prnt = obj
		self.ProcData = procData

		self.layout = QGridLayout()
		self.layout.setSpacing(0)
		#print [self.ProcData]
		if len(self.ProcData) == 0 or self.ProcData['count'] == 0 :
			self.errorLabel = QLabel('<font color=red size=7>ERROR</font>')
			self.layout.addWidget(self.errorLabel, 0, 0, 2, 4, Qt.AlignCenter)
			self.setLayout(self.layout)
			return None

		self.comboGovernorMenu = QComboBox(self)
		if 0 in self.ProcData['online'] :
			_availableGovernors = self.ProcData['availableGovernors'][0].data()[QString('contents')].toString().replace('\n', '')
		else : _availableGovernors = QString('default')
		availableGovernors = QStringList(_availableGovernors.split(' ', QString.SkipEmptyParts))
		availableGovernors.append('powersave')
		availableGovernors.append('conservative')
		#for item in availableGovernors : print '\t', item
		if 0 in self.ProcData['online'] :
			currentGovernor = self.ProcData['currentGovernor'][0].data()[QString('contents')].toString().replace('\n', '')
		else : currentGovernor = 'default'
		currGovernorIdx = availableGovernors.indexOf(currentGovernor)
		availableGovernors.removeDuplicates()
		for governor in availableGovernors :
			if os.path.isfile(iconDir + '/' + governor + '.png') :
				path_ = iconDir + '/' + governor + '.png'
			else :
				path_ = iconDir + '/ondemand.png'
			self.comboGovernorMenu.addItem(QIcon(path_), governor)
			if governor == currentGovernor : self.prnt.icon.setIcon(path_)
		#print [currentGovernor], currGovernorIdx, [item for item in availableGovernors]
		self.comboGovernorMenu.setCurrentIndex(currGovernorIdx)
		self.comboGovernorMenu.setEditable(False)
		self.comboGovernorMenu.currentIndexChanged[int].connect(self.changeRegime)
		self.layout.addWidget(self.comboGovernorMenu, 1, 2)

		self.comboMinFreq = QComboBox(self)
		#self.comboMinFreq.setMinimumContentsLength(8)
		if 0 in self.ProcData['online'] :
			_availableFreqs = self.ProcData['availableFreqs'][0].data()[QString('contents')].toString().replace('\n', '')
		else : _availableFreqs = QString('')
		availableFreqs = QStringList(_availableFreqs.split(' ', QString.SkipEmptyParts))
		#for item in availableFreqs : print '\t', item
		for j in availableFreqs :
			if j == 'default' : continue
			self.comboMinFreq.addItem(str(j)[:-3])
		self.comboMinFreq.addItem('default')
		if 0 in self.ProcData['online'] :
			currentMinFreq = self.ProcData['currentMinFreq'][0].data()[QString('contents')].toString().replace('\n', '')
		else : currentMinFreq = 'default'
		currMinFreqIdx = availableFreqs.indexOf(currentMinFreq)
		self.comboMinFreq.setCurrentIndex(currMinFreqIdx)
		self.comboMinFreq.currentIndexChanged[int].connect(self.changeRegime)
		self.layout.addWidget(self.comboMinFreq, 1, 3)

		self.comboMaxFreq = QComboBox(self)
		#self.comboMaxFreq.setMinimumContentsLength(8)
		if 0 in self.ProcData['online'] :
			_availableFreqs = self.ProcData['availableFreqs'][0].data()[QString('contents')].toString().replace('\n', '')
		else : _availableFreqs = QString('')
		availableFreqs = QStringList(_availableFreqs.split(' ', QString.SkipEmptyParts))
		#for item in availableFreqs : print '\t', item
		for j in availableFreqs :
			if j == 'default' : continue
			self.comboMaxFreq.addItem(str(j)[:-3])
		self.comboMaxFreq.addItem('default')
		if 0 in self.ProcData['online'] :
			currentMaxFreq = self.ProcData['currentMaxFreq'][0].data()[QString('contents')].toString().replace('\n', '')
		else : currentMaxFreq = 'default'
		currMaxFreqIdx = availableFreqs.indexOf(currentMaxFreq)
		self.comboMaxFreq.setCurrentIndex(currMaxFreqIdx)
		self.comboMaxFreq.currentIndexChanged[int].connect(self.changeRegime)
		self.layout.addWidget(self.comboMaxFreq, 1, 4)

		self.setLayout(self.layout)

	def getNewProcParemeters(self):
		newParameters = {}
		for i in xrange(COUNT_PROC) :

			newParameters[i] = {}
			newParameters[i]['regime'] = self.comboGovernorMenu.currentText()
			value = self.comboMinFreq.currentText()
			if value != 'default' : value += '000'
			newParameters[i]['minfrq'] = value
			value = self.comboMaxFreq.currentText()
			if value != 'default' : value += '000'
			newParameters[i]['maxfrq'] = value

		return newParameters

	def changeRegime(self, data = None):
		#print data, type(data)
		if type(data) is dict :
			global COUNT_PROC
			COUNT_PROC = len(data)
			newParameters = data
		else :
			newParameters = self.getNewProcParemeters()
		paramProc = ''
		for i in xrange(COUNT_PROC) :
			paramProc += newParameters[i]['regime'] + ' ' + \
						 newParameters[i]['minfrq'] + ' ' + \
						 newParameters[i]['maxfrq'] + ';;'
			""" 'default' ignored for set system defaults for current proc"""
			#print i, 'governor', newParameters[i]['regime']
			if newParameters[i]['regime'] != 'default' : writeCpuData(i, 'governor', newParameters[i]['regime'])
			#print i, 'min_freq', newParameters[i]['minfrq']
			if newParameters[i]['minfrq'] != 'default' : writeCpuData(i, 'min_freq', newParameters[i]['minfrq'])
			#print i, 'max_freq', newParameters[i]['maxfrq']
			if newParameters[i]['maxfrq'] != 'default' : writeCpuData(i, 'max_freq', newParameters[i]['maxfrq'])

		if type(data) is not dict :
			self.prnt.Settings.setValue('Parameters', paramProc)
			self.prnt.Settings.sync()
		self.prnt.parametersReset()

def CreateApplet(parent):
	return plasmaCpuFreqUtility(parent)
