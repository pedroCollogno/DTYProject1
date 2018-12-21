# Mobil'IOT

## Intro globale

Mobil'IOT est un projet visant à développer un objet connecté à l'application Mobil'IT V2, qui permettrait aux inspecteurs de réaliser facilement différentes mesures sur le terrain ;

* De *distances* (P0)
* De luminosité (P1)
* De niveau sonore (P1)

**Disclaimer:**

La documention de l'objet ne remplace pas celle de l'appli, mais en est plutôt un complément.

### Qui l'a développée ?

Mobili'IOT est un projet qui a démarré le 10 septembre 2018 et qui regroupe quatre étudiants de CentraleSupélec dans le cadre de la Digital Tech Year, en lien avec le projet Mobil'IT V2, qui vise une refonte de l'appli, avec 4 autres étudiants.

Projet Mobil'IOT :

* BELIGON Mathieu [mathieu.beligon@student.ecp.fr](mailto:mathieu.beligon@student.ecp.fr)
* COLLIGNON Pierre [pierre.collignon@supelec.fr](mailto:pierre.collignon@supelec.fr)
* CORDELLE Antoine [antoine.cordelle@supelec.fr](mailto:antoine.cordelle@supelec.fr)
* FEDRIGO Mathieu [mathieu.fedrigo@supelec.fr](mailto:mathieu.fedrigo@supelec.fr)

Projet Mobil'IT V2 :

* GOUTALLIER Arthur [arthur.goutallier@student.ecp.fr](mailto:arthur.goutallier@student.ecp.fr)
* KADIRI Hamza  [hamza.kadiri@student.ecp.fr](mailto:hamza.kadiri@student.ecp.fr)
* LUCAS Hadrien [hadrien.lucas@student.ecp.fr](mailto:hadrien.lucas@student.ecp.fr)
* VIOSSAT Paul [paul.viossat@student.ecp.fr](mailto:paul.viossat@student.ecp.fr)

## Mise en place de l'application

Voir le REAMDE de l'application, qui reprend l'installation en local de l'app et de la bdd associée.

------------------------------------------------------------------------------------------


# Le prototype

## Matériel nécessaire

Voici le matériel nécessaire pour prototyper l'objet:

* [Un capteur de distance TFMini](https://www.amazon.fr/UNIKEL-D%C3%A9tecteur-Ranging-Unidirectionnel-Raspberry/dp/B07C7CXMHR/ref=sr_1_cc_1?s=aps&ie=UTF8&qid=1536832527&sr=1-1-catcorr&keywords=Lidar+TF-MINI)
* [Un capteur de volume sonore KY-037](https://www.amazon.fr/Carte-AZDelivery-pour-Arduino-microphone/dp/B07CN3D77S/ref=sr_1_1?ie=UTF8&qid=1536834197&sr=8-1&keywords=KY-037)
* [Un capteur de luminosité BH1750](https://www.amazon.fr/Capteur-Luminosit%C3%A9-Couteau-temt6000-Analogique-prototypage/dp/B01N5KZCQJ/ref=sr_1_3?ie=UTF8&qid=1536835017&sr=8-3&keywords=TEMT6000)
* [Un module bluetooth HM-10](https://www.amazon.fr/DSD-TECH-Bluetooth-iBeacon-Arduino/dp/B06WGZB2N4/ref=sr_1_10?s=computers&ie=UTF8&qid=1536837058&sr=1-10&keywords=bluetooth+arduino)
* [Un module 4*7 segments](https://www.amazon.fr/AZDelivery-Digital-Display-Arduino-Raspberry/dp/B078S8SGW2/ref=pd_sbs_147_3?_encoding=UTF8&pd_rd_i=B078S8SGW2&pd_rd_r=47c19465-b752-11e8-ae07-77c04c60f3a3&pd_rd_w=EFM5z&pd_rd_wg=Vl45f&pf_rd_i=desktop-dp-sims&pf_rd_m=A1X6FK5RDHNB96&pf_rd_p=090bc395-5f65-417a-910c-c1aa58a5be54&pf_rd_r=0DGASJX343PNZ7B017K0&pf_rd_s=desktop-dp-sims&pf_rd_t=40701&psc=1&refRID=0DGASJX343PNZ7B017K0)
* 4 boutons poussoir
* 3 leds
* [Un buzzer](https://www.amazon.fr/Buzzer-Actif-continu-Arduino-Domotique/dp/B00GX6YCBI/ref=sr_1_2?ie=UTF8&qid=1536847481&sr=8-2&keywords=piezo+buzzer)
* Une carte Arduino Nano
* Des piles 9V
* [Des adaptateurs pour les piles](https://www.amazon.fr/KEESIN-batterie-bouton-Prise-Support/dp/B06Y41ZRVJ/ref=sr_1_6?s=electronics&ie=UTF8&qid=1536844571&sr=1-6&keywords=batterie+pile+arduino)


## Cablage

Voir le dossier PCB, et s'assurer que les pins sur le code (fichier ino) sont bien configurés.


## Code

Il faut adapter à votre prototype:

* Les pins (fichier pins.hpp) si besoin ;
* Le nombre de capteurs (fichiers MobilIOT.ino), et leur type.

Transférer le code MobilIOT sur la nano, et enjoy !

## Documentation

# Les composants

LUX (nouveau capteur) : [github.com/claws/BH1750](github.com/claws/BH1750)

DIST : [github.com/TFmini/TFmini-Arduino](github.com/TFmini/TFmini-Arduino)

TEMPERATURE : [https://www.carnetdumaker.net/articles/mesurer-une-temperature-avec-un-capteur-1-wire-ds18b20-et-une-carte-arduino-genuino/](https://www.carnetdumaker.net/articles/mesurer-une-temperature-avec-un-capteur-1-wire-ds18b20-et-une-carte-arduino-genuino/)

## Le code

### Librairies utilisées

 - DallasTemperature (capteur de température)
 - TFMini (lidar)
 - TM1637Display (7segments)
 - https://github.com/tedyapo/arduino-VEML7700 (luxmeter)

### Organisation

Le fichier main doit renseigner les différents Capteurs, qui permettent d'accéder aux grandeurs mesurées, à l'unité à afficher sur le 7 segments, ainsi qu'aux pins de la led et du bouton correspondant au capteur.

Pour rajouter un nouveau capteur, il suffit donc d'hériter de la classe Capteur, de redéfinir les méthodes nécessaires, et d'instancier ce capteur dans la liste du fichier main, en renseignant ses pins.
