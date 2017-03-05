#Kyle Martin krm504@nyu.edu
#For ICTF - checks whether our srevices are down.
#2017 reported that all services for everyone were always untested.  No fix known.

import ictf
from ictf import iCTF

didntwork = True
while didntwork:
	try:
		#Login
		i = iCTF()
		t = i.login('nmg355@nyu.edu', 'tVxVEVsUwvPZfehU')
		
		game = t.get_game_status()
		#Make sure we're in the game! Get our ID #... Also collect everyone's ID because comeon: NSA
		allIDs = {}
		for info in game['teams']:
			allIDs[unicode(info[u'id'])] = unicode(info[u'name'])
			if info[u'name'] == u'NYUSEC':
				id = unicode(info[u'id'])
		
		print("Our id is: " + id)
		print("We are playing against " + str(len(allIDs)) + " teams.")
		
		#Safe, ready to roll
		didntwork = False
		
		#print(game['scores'][id])
		
		#Get data on our services
		ourTeamServiceStats = game['service_states'][id]
		#print(ourTeamServiceStats)
		for serviceId in ourTeamServiceStats:
		
			#print("u'" + str(serviceId) + "':")
			#print(" " + str(ourTeamServiceStats[serviceId]))
			
			if ourTeamServiceStats[serviceId][u'service_state'] == u'down':
				print("WARNING, " + str(ourTeamServiceStats[serviceId][u'service_name']) + "is down")
		
		"""
		untestedTeams = {}
		allTeams = game['service_states']
		##print allTeams.keys()
		for teamID in allTeams:
			for serviceId in allTeams[teamID]:
				if allTeams[teamID][serviceId][u'service_state'] == u'untested':
					untestedTeams[teamID] = 0
					#print("WARNING, " + str(allTeams[teamID][serviceId][u'service_name']) + "is untested, for team: " + str(teamID))
		
		#Sanity Check for this API, checks to see if _anyone_ has yet been tested:
		for teamIdder in allIDs.keys():
			if not teamIdder in untestedTeams:
				print("Team " + str(teamIdder) + " has been tested.")
		"""
	except: #Not the safest way, but whatever?
		continue
		
#Get Support Tickets?:
#t.get_support_tickets()
