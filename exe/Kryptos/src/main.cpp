
#include <iostream>
#include <VigenereCipher.h>
#include <SubstitutionCipher.h>
#include <DoubleSubstitutionCipher.h>
#include <ModularTranspositionCipher.h>
#include <utility>

void main(){

	// Kryptos Data
	std::string k1  = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFD";
	std::string k1D = "BETWEENSUBTLESHADINGANDTHEABSENCEOFLIGHTLIESTHENUANCEOFIQLUSION";
	//                '0         1         2         3         4         5     *   6   '
	// "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	// '01234567890123456789012345'

	std::string k2  = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKK?DQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVH?DWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZ?FKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG";
	std::string k2D = "ITWASTOTALLYINVISIBLEHOWSTHATPOSSIBLE?THEYUSEDTHEEARTHSMAGNETICFIELDXTHEINFORMATIONWASGATHEREDANDTRANSMITTEDUNDERGRUUNDTOANUNKNOWNLOCATIONXDOESLANGLEYKNOWABOUTTHIS?THEYSHOULDITSBURIEDOUTTHERESOMEWHEREXWHOKNOWSTHEEXACTLOCATION?ONLYWWTHISWASHISLASTMESSAGEXTHIRTYEIGHTDEGREESFIFTYSEVENMINUTESSIXPOINTFIVESECONDSNORTHSEVENTYSEVENDEGREESEIGHTMINUTESFORTYFOURSECONDSWESTIDBYROWS";
	//                '0         1         2         3         4         5         6         7         8         9         0         1    *    2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7 '

	std::string k3  = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?";
	std::string k3D = "SLOWLYDESPARATLYSLOWLYTHEREMAINSOFPASSAGEDEBRISTHATENCUMBEREDTHELOWERPARTOFTHEDOORWAYWASREMOVEDWITHTREMBLINGHANDSIMADEATINYBREACHINTHEUPPERLEFTHANDCORNERANDTHENWIDENINGTHEHOLEALITTLEIINSERTEDTHECANDLEANDPEEREDINTHEHOTAIRESCAPINGFROMTHECHAMBERCAUSEDTHEFLAMETOFLICKERBUTPRESENTLYDETAILSOFTHEROOMWITHINEMERGEDFROMTHEMISTXCANYOUSEEANYTHINGQ?";

	/*
	SLOWLY  DESPARAT LY SLOWLY      THE REMAINS OF PASSAGE DEBRIS THAT ENCUMBERED THE LOWER PART OF THE DOORWAY WAS REMOVED      WITH TREMBLING HANDS I MADE A TINY BREACH IN THE UPPER LEFT HAND CORNER     AND THEN  WIDENING THE HOLE A LITTLE  I INSERTED THE CANDLE AND PEERED IN     THE HOT AIR ESCAPING FROM THE CHAMBER CAUSED THE FLAME TO FLICKER          BUT PRESENTLY     DETAILS OF THE ROOM WITHIN EMERGED     FROM THE MIST X    CAN YOU SEE ANYTHING Q?"
	            *   *
	Slowly, desperately slowly ... the remains of passage debris that encumbered the lower part of the doorway were removed ... With trembling hands I made a tiny breach in the upper left hand corner ... and then, widening the hole a little, I inserted the candle and peered in ... the hot air escaping from the chamber causing the candle flame to flicker, but presently ... details of the room within emerged ... from the mist ... 'Can you see anything?'
	Slowly, desperately slowly it seemed to us as we watched, the remains of passage debris that encumbered the lower part of the doorway were removed, until at last we had the whole door clear before us. The decisive moment had arrived. With trembling hands I made a tiny breach in the upper left hand corner. Darkness and blank space, as far as an iron testing-rod could reach, showed that whatever lay beyond was empty, and not filled like the passage we had just cleared. Candle tests were applied as a precaution against possible foul gases, and then, widening the hole a little, I inserted the candle and peered in, Lord Carnarvon, Lady Evelyn [Lord Carnarvon's daughter] and Callender [an assistant] standing anxiously beside me to hear the verdict. At first I could see nothing, the hot air escaping from the chamber causing the candle flame to flicker, but presently, as my eyes grew accustomed to the light, details of the room within emerged slowly from the mist, strange animals, statues, and gold - everywhere the glint of gold. For the moment - an eternity it must have seemed to the others standing by - I was struck dumb with amazement, and when Lord Carnarvon, unable to stand the suspense any longer, inquired anxiously, 'Can you see anything?' it was all I could do to get out the words, 'Yes, wonderful things.' Then widening the hole a little further, so that we both could see, we inserted an electric torch.

	enigma_cxx.exe OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABERLINAAAAAAAAAAAAAAAAAAAAAAAAAAAA ...............................................................BERLIN............................

	*/

	std::string k4 = "OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";


	// Kryptos Part 1
	std::string k1d = Crypt::DoubleSubstitutionCipher::decrypt(k1,std::pair<Crypt::CryptString,Crypt::CryptString>("kryptos","palimpsest"));
	std::cout<<"K1:"<<std::endl;
	std::cout<<k1d<<std::endl;
	std::cout<<std::endl;

	// Kryptos Part 2
	std::string k2d = Crypt::DoubleSubstitutionCipher::decrypt(k2,std::pair<Crypt::CryptString,Crypt::CryptString>("kryptos","abscissa"));
	std::cout<<"K2:"<<std::endl;
	std::cout<<k2d<<std::endl;	
	std::cout<<std::endl;

	// Kryptos Part 3
	std::string k3d = Crypt::ModularTranspositionCipher::decrypt(k3,std::pair<int,int>(192,337));
	std::cout<<"K3:"<<std::endl;
	std::cout<<k3d<<std::endl;
	std::cout<<std::endl;

	// Kryptos Part 4
	std::string k4d = Crypt::DoubleSubstitutionCipher::decrypt(k4,std::pair<Crypt::CryptString,Crypt::CryptString>("kryptos","kryptos"));
	std::cout<<"K5:"<<std::endl;
	std::cout<<k4d<<std::endl;
	std::cout<<std::endl;

}