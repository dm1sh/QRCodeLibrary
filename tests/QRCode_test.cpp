﻿#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/QRCode.hpp"

TEST(QRCodeTests, ConstructsClass) {
	QRCode qr("TESTTESTTESTTESTTESTTEST");

	EXPECT_EQ(qr.input, str_to_bytes("TESTTESTTESTTESTTESTTEST"));
	EXPECT_EQ(qr.corr_lvl, CorrectionLevel::M);
	EXPECT_EQ(qr.method, QRCodeMethod::Alphabetic);
	EXPECT_EQ(qr.version, 1);
}

TEST(QRCodeTests, CreatesQRCode) {
	//QRCode qr(std::string("Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, “and what is the use of a book,” thought Alice “without pictures or conversations?”\n"
	//					  "So she was considering in her own mind(as well as she could, for the hot day made her feel very sleepyand stupid), whether the pleasure of making a daisy - chain would be worth the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink eyes ran close by her.\n"
	//					  "There was nothing so very remarkable in that; nor did Alice think it so very much out of the way to hear the Rabbit say to itself, “Oh dear! Oh dear! I shall be late!” (when she thought it over afterwards, it occurred to her that she ought to have wondered at this, but at the time it all seemed quite natural);"
	//					  "but when the Rabbit actually took a watch out of its waistcoat - pocket, and looked at it, and then hurried on, Alice started to her feet, for it flashed across her mind that she had never before seen a rabbit with either a waistcoat - pocket, or a watch to take out of it, and burning with curiosity, she ran across the field after it, and fortunately was just in time to see it pop down a large rabbit - hole under the hedge."
	//					  "In another moment down went Alice after it, never once considering how in the world she was to get out again."
	//					  "The rabbit-hole went straight on like a tunnel for some way, and then dipped suddenly down, so suddenly that Alice had not a moment to think about stopping herself before she found herself falling down a very deep well."
	//					  "Either the well was very deep, or she fell very slowly, for she had plenty of time as she went down to look about her and to wonder what was going to happen next. First, she tried to look down and make out what she was coming to, but it was too dark to see anything; then she looked at the sides of the well, and noticed that they were filled with cupboards and book-shelves; here and there she saw maps and pictures hung upon pegs. She took down a jar from one of the shelves as she passed; it was labelled “ORANGE MARMALADE”, but to her great disappointment it was empty: she did not like to drop the jar for fear of killing somebody underneath, so managed to put it into one of the cupboards as she fell past it."
	//					  "“Well!” thought Alice to herself, “after such a fall as this, I shall think nothing of tumbling down stairs! How brave they’ll all think me at home! Why, I wouldn’t say anything about it, even if I fell off the top of the house!” (Which was very likely true.)"
	//					  "Down, down, down. Would the fall never come to an end? “I wonder how many miles I’ve fallen by this time?” she said aloud. “I must be getting somewhere near the centre of the earth. Let me see: that would be four thousand miles down, I think—” (for, you see, Alice had learnt several things of this sort in her lessons )"
	//					  ), CorrectionLevel::L);

	//QRCode qr(std::string("ALICE WAS BEGINNING TO GET VERY TIRED OF SITTING BY HER SISTER ON THE BANK AND OF HAVING NOTHING TO DO: ONCE OR TWICE SHE HAD PEEPED INTO THE BOOK HER SISTER WAS READING BUT IT HAD NO PICTURES OR CONVERSATIONS IN IT AND WHAT IS THE USE OF A BOOK THOUGHT ALICE WITHOUT PICTURES OR CONVERSATIONS. SO SHE WAS CONSIDERING IN HER OWN MIND AS WELL AS SHE COULD FOR THE HOT DAY MADE HER FEEL VERY SLEEPY AND STUPID. WHETHER THE PLEASURE OF MAKING A DAISY-CHAIN WOULD BE WORTH THE TROUBLE OF GETTING UP AND PICKING THE DAISIES WHEN SUDDENLY A WHITE RABBIT WITH PINK EYES RAN CLOSE BY HER. THERE WAS NOTHING SO VERY REMARKABLE IN THAT NOR DID ALICE THINK IT SO VERY MUCH OUT OF THE WAY TO HEAR THE RABBIT SAY TO ITSELF OH DEAR. OH DEAR. I SHALL BE LATE. WHEN SHE THOUGHT IT OVER AFTERWARDS IT OCCURRED TO HER THAT SHE OUGHT TO HAVE WONDERED AT THIS BUT AT THE TIME IT ALL SEEMED QUITE NATURAL. BUT WHEN THE RABBIT ACTUALLY TOOK A WATCH OUT OF ITS WAISTCOAT-POCKET AND LOOKED AT IT AND THEN HURRIED ON ALICE STARTED TO HER FEET FOR IT FLASHED ACROSS HER MIND THAT SHE HAD NEVER BEFORE SEEN A RABBIT WITH EITHER A WAISTCOAT-POCKET OR A WATCH TO TAKE OUT OF IT AND BURNING WITH CURIOSITY SHE RAN ACROSS THE FIELD AFTER IT AND FORTUNATELY WAS JUST IN TIME TO SEE IT POP DOWN A LARGE RABBIT-HOLE UNDER THE HEDGE. IN ANOTHER MOMENT DOWN WENT ALICE AFTER IT NEVER ONCE CONSIDERING HOW IN THE WORLD SHE WAS TO GET OUT AGAIN. THE RABBIT-HOLE WENT STRAIGHT ON LIKE A TUNNEL FOR SOME WAY AND THEN DIPPED SUDDENLY DOWN SO SUDDENLY THAT ALICE HAD NOT A MOMENT TO THINK ABOUT STOPPING HERSELF BEFORE SHE FOUND HERSELF FALLING DOWN A VERY DEEP WELL. EITHER THE WELL WAS VERY DEEP OR SHE FELL VERY SLOWLY FOR SHE HAD PLENTY OF TIME AS SHE WENT DOWN TO LOOK ABOUT HER AND TO WONDER WHAT WAS GOING TO HAPPEN NEXT. FIRST SHE TRIED TO LOOK DOWN AND MAKE OUT WHAT SHE WAS COMING TO BUT IT WAS TOO DARK TO SEE ANYTHING THEN SHE LOOKED AT THE SIDES OF THE WELL AND NOTICED THAT THEY WERE FILLED WITH CUPBOARDS AND BOOK-SHELVES HERE AND THERE SHE SAW MAPS AND PICTURES HUNG UPON PEGS. SHE TOOK DOWN A JAR FROM ONE OF THE SHELVES AS SHE PASSED IT WAS LABELLED ORANGE MARMALADE BUT TO HER GREAT DISAPPOINTMENT IT WAS EMPTY: SHE DID NOT LIKE TO DROP THE JAR FOR FEAR OF KILLING SOMEBODY UNDERNEATH SO MANAGED TO PUT IT INTO ONE OF THE CUPBOARDS AS SHE FELL PAST IT. WELL. THOUGHT ALICE TO HERSELF AFTER SUCH A FALL AS THIS I SHALL THINK NOTHING OF TUMBLING DOWN STAIRS. HOW BRAVE THEYLL ALL THINK ME AT HOME. WHY I WOULDNT SAY ANYTHING ABOUT IT EVEN IF I FELL OFF THE TOP OF THE HOUSE. WHICH WAS VERY LIKELY TRUE.. DOWN DOWN DOWN. WOULD THE FALL NEVER COME TO AN END. I WONDER HOW MANY MILES IVE FALLEN BY THIS TIME. SHE SAID ALOUD. I MUST BE GETTING SOMEWHERE NEAR THE CENTRE OF THE EARTH. LET ME SEE: THAT WOULD BE FOUR THOUSAND MILES DOWN I THINK- FOR YOU SEE ALICE HAD LEARNT SEVERAL THINGS OF THIS SORT IN HER LESSONS IN THE SCHOOLROOM AND THOUGH THIS WAS NOT A VERY GOOD OPPORTUNITY FOR SHOWING OFF HER KNOWLEDGE AS THERE WAS NO ONE TO LISTEN TO HER STILL IT WAS GOOD PRACTICE TO SAY IT OVER. -YES THATS ABOUT THE RIGHT DISTANCE-BUT THEN I WONDER WHAT LATITUDE OR LONGITUDE IVE GOT TO. ALICE HAD NO IDEA WHAT LATITUDE WAS OR LONGITUDE EITHER BUT THOUGHT THEY WERE NICE GRAND WORDS TO SAY.. PRESENTLY SHE BEGAN AGAIN. I WONDER IF I SHALL FALL RIGHT THROUGH THE EARTH. HOW FUNNY ITLL SEEM TO COME OUT AMONG THE PEOPLE THAT WALK WITH THEIR HEADS DOWNWARD. THE ANTIPATHIES I THINK- SHE WAS RATHER GLAD THERE WAS NO ONE LISTENING THIS TIME AS IT DIDNT SOUND AT ALL THE RIGHT WORD. -BUT I SHALL HAVE TO ASK THEM WHAT THE NAME OF THE COUNTRY IS YOU KNOW. PLEASE MAAM IS THIS NEW ZEALAND OR AUSTRALIA. AND SHE TRIED TO CURTSEY AS SHE SPOKE-FANCY CURTSEYING AS YOURE FALLING THROUGH THE AIR. DO YOU THINK YOU COULD MANAGE IT.. AND WHAT AN IGNORANT LITTLE GIRL SHELL THINK ME FOR ASKING. NO ITLL NEVER DO TO ASK: PERHAPS I SHALL SEE IT WRITTEN UP SOMEWHERE. DOWN DOWN DOWN. THERE WAS NOTHING ELSE TO DO SO ALICE SOON BEGAN TALKING AGAIN. DINAHLL MISS ME VERY MUCH TO-NIGHT I SHOULD THINK. DINAH WAS THE CAT.. I HOPE THEYLL REMEMBER HER SAUCER OF MILK AT TEA-TIME. DINAH MY DEAR. I WISH YOU WERE DOWN HERE WITH ME. THERE ARE NO MICE IN THE AIR IM AFRAID BUT YOU MIGHT CATCH A BAT AND THATS VERY LIKE A MOUSE YOU KNOW. BUT DO CATS EAT BATS I WONDER. AND HERE ALICE BEGAN TO GET RATHER SLEEPY AND WENT ON SAYING TO HERSELF IN A DREAMY SORT OF WAY DO CATS EAT BATS. DO CATS EAT BATS. AND SOMETIMES DO BATS EAT CATS. FOR YOU SEE AS SHE COULDNT ANSWER EITHER QUESTION IT DIDNT MUCH MATTER WHICH WAY SHE PUT IT. SHE FELT THAT SHE WAS DOZING OFF AND HAD JUST BEGUN TO DREAM THAT SHE WAS WALKING HAND IN HAND WITH DINAH AND SAYING TO HER VERY EARNESTLY NOW DINAH TELL ME THE TRUTH: DID YOU EVER EAT A BAT. WHEN SUDDENLY THUMP. THUMP. DOWN SHE CAME UPON A HEAP OF STICKS AND DRY LEAVES AND THE FALL WAS OVER."
	//).substr(0, 4296), CorrectionLevel::L);

	string input(u8"Здравствуйте, я - QR-код, сгенерированный при помощи библиотеки QRCodeLibrary!");

	QRCode qr(input);

	EXPECT_EQ(qr.to_string(), "1111111000000000111011111011101110111100101111111\n1000001010110100000100010001000100010111101000001\n1011101000110110000110011101101110110101101011101\n1011101000000001001000110010111011111001001011101\n1011101011001100001011111110110011001000001011101\n1000001000011100110000100011100110010010001000001\n1111111010101010101010101010101010101010101111111\n0000000001001100101101100010101011010001000000000\n1010101000011111111001111110000000100110000010010\n0100100111010011010101000101001100100010000001001\n0110011111011011101010101000111011101110001110100\n1111110111010011101111100011010101101011010010110\n1101101110011100001011010110001000100011001001101\n0000000010001100100010111010011001010011101101000\n0000001100000100000000001110110010001110111010000\n0001010111110010001010110101001100110101010100010\n0000101101000100100100100011000100010111011000101\n1000100110101101101111000111101110111001101000000\n0110101010010101110010001101001100110100111011011\n1000010011011011101101000010110011000101001100100\n1000011000000001011100011000001001110111010001101\n1000010110101001100111010011011101100111101000010\n0101111110101001111010111110110010100010111110100\n0010100010001100100101100010010001000101100011000\n0010101010011001000111101011001100110010101010001\n0001100011101010100011100011011101100111100011000\n0111111110001110000001111110110011011101111110110\n1100000011010010110111110100010001000100100101111\n0000011101001011101110001011011100110010110001010\n1101010111010010001100101101001000111110010001000\n1111101010111111000110000010111001101100011011010\n1101100100011110010101101110010001010101111000010\n0000011010101010111110101010111011101001101110001\n0100010011110100100011111100010001000000110011000\n1011111100001000011000111000111011101101000010111\n0010010011010010000110110010000001010101101101110\n0000011101011110010110011101011101000111001111001\n0111110110101010101010101110110000100010010010100\n0100011111100001111010011100000011101110000010110\n0111000000000001111100101000110101101011101101001\n1110001010101100010100111110000000100111111110010\n0000000011110111100111100011001000110011100011101\n1111111001001101101011101010111011101110101010100\n1000001001000100110101100011110011010011100011010\n1011101011010000110010111110101000100000111110001\n1011101001100101111011111101011101100011110000110\n1011101011110010011000101111010011001111101101000\n1000001000100101011011000101001100111110011100010\n1111111011110000101100010111000100001110010110011");
}
