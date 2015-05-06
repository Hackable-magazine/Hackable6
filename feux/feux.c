#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY_VERT          10
#define DELAY_JAUNE          2
#define DELAY_ROUGE         10
#define DEMI_PERIODE_ALARME  1

#define LED_VERTE PB0
#define LED_JAUNE PB1
#define LED_ROUGE PB2
#define BUZZER    PB3
#define BOUTON    PB4

// compteur pour les itérations d'interruptions
int its_counter = 0;

// booléen pour le clignotement de la led rouge
int ledRouge = 1;

// états possibles
enum {vert,jaune,rouge,alarme} etat = vert;

int main(void)
{
// On configure les entrées/sorties 0, 1 et 2 du port B en mode sortie
DDRB = 0;
DDRB |= (1<<LED_VERTE);
DDRB |= (1<<LED_JAUNE);
DDRB |= (1<<LED_ROUGE);

// on configure la 4 en entrée
DDRB |= (0<<BOUTON);
// et on active le PULL UP
PORTB |= (1<<BOUTON);

// et la 3 en sortie pour le buzzer
DDRB |= (1<<BUZZER);

// On allume la led verte et on éteint les leds jaune et rouge
PORTB |= (1<<LED_VERTE);
PORTB &=~ (1<<LED_JAUNE);
PORTB &=~ (1<<LED_ROUGE);

// mesure du temps par interruption
// on configure le diviseur sur 256
TCCR0B |= (1<<CS02);
// on active les interruptions pour débordement du compteur 0
TIMSK |= (1<<TOIE0);

// on active les interruptions par changement d'état des broches du portB
GIMSK |= (1<<PCIE);
// seul le changement d'état sur BOUTON (PB4) déclenchera une interruption
PCMSK |= (1<<PCINT4);

// on active les interruptions
sei();

// le programme est une boucle infinie, qui ne fait rien !
while(1){};

return 0;
}

// macro qi s'exécute lors d'un débordement du compteur 0
// (TIMer 0 Overflow)
ISR(TIM0_OVF_vect){
	// on désactive les interruptions pour ne pas boucler
	cli();

	// on teste les différents états
	switch(etat){
		case vert:
			if(++its_counter>=(122*DELAY_VERT)){
				its_counter = 0;
				// on éteint les leds verte et rouge et on allume la jaune
				PORTB &=~ (1<<LED_VERTE);
				PORTB |=  (1<<LED_JAUNE);
				PORTB &=~  (1<<LED_ROUGE);
				etat = jaune;
			};
			break;
		case jaune:
			if(++its_counter>= (122*DELAY_JAUNE)){
				its_counter = 0;
				// on éteint les leds verte et le jaune et on allume la rouge
				PORTB &=~ (1<<LED_VERTE);
				PORTB &=~ (1<<LED_JAUNE);
				PORTB |=  (1<<LED_ROUGE);
				etat = rouge;
			};
			break;
		case rouge:
			if(++its_counter>=(122*DELAY_ROUGE)){
				its_counter = 0;
				// on éteint les led jaune et le rouge et on allume la verte
				PORTB |=  (1<<LED_VERTE);
				PORTB &=~ (1<<LED_JAUNE);
				PORTB &=~ (1<<LED_ROUGE);
				etat = vert;
			};
			break;
		case alarme:
			// on éteint les leds verte et jaune
			PORTB &=~ (1<<LED_VERTE);
			PORTB &=~ (1<<LED_JAUNE);
			// si la led rouge est allumée, on émet un son
			if(ledRouge){
				PORTB |= (1<<LED_ROUGE);
				int i;
				for(i=0;i<500*DEMI_PERIODE_ALARME;i++){
				PORTB |=  (1<<BUZZER);
				_delay_ms(1);
				PORTB &=~ (1<<BUZZER);
				_delay_ms(1);}
				PORTB &=~ (1<<LED_ROUGE);
				ledRouge = 0;
			}
			// sinon on attend
			else
			{
				_delay_ms(1000*DEMI_PERIODE_ALARME);
				ledRouge = 1;
			}
			break;
	}	

	// on réactive les interruptions
	sei();
}

ISR(PCINT0_vect){
	cli();
	// on attend 20 ms pour éviter les rebonds au niveau du contact
	// du bouton poussoir
	_delay_ms(20);

	// si c'est un appui et pas un relâchement
	if(!(PINB & (1<<PINB4)))
	{
	  // si l'alarme était déjà activée, on la désactive et on revient
	  // dans un état normal
	  if(etat == alarme){
		etat = vert;
		// On allume la led verte et on éteint les autres
		PORTB |=  (1<<LED_VERTE);
		PORTB &=~ (1<<LED_JAUNE);
		PORTB &=~ (1<<LED_ROUGE);
		its_counter = 0;}
	  // sinon, on active l'alarme
	  else{
		ledRouge = 1;
		etat = alarme;}
	}
	sei();
}
