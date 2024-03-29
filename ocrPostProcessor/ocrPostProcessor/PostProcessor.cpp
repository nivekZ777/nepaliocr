//Author : Rajesh Pandey
//Email: pandey.pandey@gmail.com, rajesh@mpp.org.np
//Sunday October 26, 2008
//Madan Puraskar Pustakalaya
//Program for processing the output provided by Nepali OCR
#include "StdAfx.h"
#include "PostProcessor.h"

 bool PostProcessor::IsDependentVowel(wchar_t Vowel)
		 {
			 //Putting the values of the  unicode characters.
			 //These values are defined by the unicode consortium
			 //Unicode values are in Hexadecimal form.
			 //We need to convert them into Decimal form before processing
			 //For example Hex value of A (अ) is 0905 whereas the decimal value is 2309
			 //We need to convert into windows xp alt keys before processing: so: converting Hex 0905 becomes 2309 in Decimal
			 //const wchar_t aakar = 2494;
			 
			 const wchar_t aakar = 2366; //ा
			 const wchar_t rossoikar =  2367; //ि 093F
			 const wchar_t dirgikar =  2368; //ी 0940
			 const wchar_t rossoUkar =  2369; //ु 0941
			 const wchar_t dirgUkar =  2370; //ू 0942
			 const wchar_t rrikar =  2371; // ृ 0943
			 const wchar_t ekar =  2375; // े 0947
			 const wchar_t oikar =  2376; //ै 0948
			 const wchar_t o_kar =  2379; //ो 094B
			 const wchar_t ou_kar =  2380; //ौ 094C
			 const wchar_t newLine = 10;// \n A
			
			// const wchar_t oo = 2313;//उ 0909

			 switch(Vowel)
			 {
			 case aakar:
			 case rossoikar:
			 case dirgikar:
			 case rossoUkar:
			 case dirgUkar:
			 case rrikar:
			 case ekar:
			 case oikar:
			 case o_kar:
			 case ou_kar:
			// case oo:
			 case newLine:

				  return true;
				 break;
			 };

			 return false;
		 }
  PostProcessor::PostProcessor(System::String^ textStr)
	{
		this->processStr = textStr;
		//Input text is textStr now assigned to the processStr
		//
	}
  System::String^ PostProcessor::TextPostProcessor()
		 {
			 int i;

			 //this->processStr = this->processStr->Trim();
			 //this step removes the extra spaces if present at the end of the text

			 cli::array<wchar_t,1>^ ch = this->processStr->ToCharArray();
			 int len = this->processStr->Length;

			 System::Collections::ArrayList^ charU = gcnew System::Collections::ArrayList(len);

			 for(i=0;i<len;i++)
			 	 charU->Add(ch[i]);

			 const wchar_t space = 32;// 
			
			 const wchar_t bug = 39;// '
			 const wchar_t Delete_del = 9676;//2492 it delete itself and also delete next to it
				
			 const wchar_t aakar = 2366; //ा
			 const wchar_t rossoikar =  2367; //ि 093F
			 const wchar_t dirgikar =  2368; //ी 0940
			 const wchar_t rossoUkar =  2369; //ु 0941
			 const wchar_t dirgUkar =  2370; //ू 0942
			 const wchar_t rrikar =  2371; // ृ 0943
			 const wchar_t ekar =  2375; // े 0947
			 const wchar_t oikar =  2376; //ै 0948
			 const wchar_t o_kar =  2379; //ो 094B
			 const wchar_t ou_kar =  2380; //ौ 094C

			 const wchar_t chandrabindu = 2305; //ँ 0901
			 const wchar_t a = 2309; //अ 0905
			 const wchar_t Aa = 2310; //आ 0906			 
			 
			 const wchar_t halanta = 2381; //् 094D
			 const wchar_t dari = 2404;
			 const wchar_t oo = 2313;//उ 0909

			 const wchar_t ga = 2327;// ग 0917
		

			 const wchar_t za = 2479;
			 const wchar_t onisar = 2434;
			 const wchar_t newLine = 10;// \n A
			 
			 for( i = 0; i < charU->Count; i++ )
			 {
 

				 if ((i+1 < charU->Count) &&
					 this->IsDependentVowel((wchar_t)charU[i]) && this->IsDependentVowel((wchar_t)charU[i+1]) )
				 {
					 //// if there is any 2 Consecutive char is vowel 
					 ///  and they are same then delete any one
					 if (charU[i]->Equals(charU[i+1]))
					 {
						 charU->RemoveAt(i);
					 }
				 }

				 if (charU[i]->Equals(onisar)) // 2434
				 {
					 // if a onisar come at the beganing of a word
					 // remove it
					 if(i-1 < 0 || charU[i-1]->Equals(space))
					 {
						 charU->RemoveAt(i);
						 i--;
					 }
				 }
				 
				 else if ( charU[i]->Equals(chandrabindu) && i+1 < charU->Count)
				 {
					 // changing position of chandrabindu with dependant vowel
					 // rule is : consonant + dependant vowel + chandrabindu
					 if ( charU[i+1]->Equals(aakar) )
					 {
						 wchar_t tmp = (wchar_t)charU[i+1];// copy aakar
						 charU[i+1] = charU[i];
						 charU[i] = tmp;
					 }
				 }
				 else if (charU[i]->Equals(halanta))//2509
				 {
					 // solving the problem of zofala
					 // zofala always sits befor dependent vowel
					 // here we r moving zofala before dependent vowel
					 if (i+1 < charU->Count && charU[i+1]->Equals(za))
					 {
						 if((i-1 > 0) && this->IsDependentVowel((wchar_t)charU[i-1]))
						 {
							 wchar_t tmp = (wchar_t)charU[i-1];// copy dependent vowel
							 charU[i-1] = charU[i];
							 charU[i] = charU[i+1];
							 charU[i+1] = tmp;
						 }
					 }// end zofala
				 }//end of halanta				 
				 else if (charU[i]->Equals(bug))//39
				 {
					 ///just remove very small dot
					 charU->RemoveAt(i);
					 i--;

				 }// end of bug
				 else if (charU[i]->Equals(Delete_del))//2492
				 {
					 // it delete itself and also delete next to it
					 charU->RemoveAt(i);
					 if (this->IsDependentVowel((wchar_t)charU[i]))
					 {
						 charU->RemoveAt(i);						 
					 }
					 i--;
				 }//end of delete

				 //////////////////////////////////////////////////////////////////////////
				 //////////////////////////////////////////////////////////////////////////
				 //////////////////////////////////////////////////////////////////////////
				 switch((wchar_t)charU[i])
				 {
				 
				 case oo: 
					 ///If there is a ookar an a(oo), then we are replace this both 
					 /// as a(Sori_O)
				    if (i+1 >= charU->Count)
					 break;
					 if (charU[i+1]->Equals(aakar))
					 {
						
					//	System::Windows::Forms::MessageBox::Show(charU[i+1]->ToString(),charU[i]->ToString());
						 charU->RemoveAt(i);
						 charU->RemoveAt(i);
						 charU->Insert(i,a);
					//	 System::Windows::Forms::MessageBox::Show(charU[i]->ToString(),a.ToString());

						  if (charU[i+1]->Equals(aakar))
						 {	 //if उ becomes अ then its possible that it might be आ so: 
							 charU->RemoveAt(i);
							 charU->RemoveAt(i);
							 charU->Insert(i,Aa);
							 
						 }
					 }
				
					 
 
				 break;
				 case a://2437
					 ///If there is a aakar agter an a(Sori_O), then we are replace this both 
					 /// as Aa(Sori_Aa)
					 if (i+1 >= charU->Count)
						 break;
					 if (charU[i+1]->Equals(aakar))
					 {
						 charU->RemoveAt(i);
						 charU->RemoveAt(i);
						 charU->Insert(i,Aa);
						 
					 }
					 break;

				 //case ga://2437
					// ///If there is a aakar agter an a(Sori_O), then we are replace this both 
					// /// as Aa(Sori_Aa)
					// if (i+1 >= charU->Count)
					//	 break;
					// if (charU[i+1]->Equals(halanta)&& charU[i+2]->Equals(aakar))
					// {
					//	 charU->RemoveAt(i);
					//	 charU->RemoveAt(i);
					//	 charU->Insert(i,ga);
					//	 
					// }
					// break;
				 case aakar://2494
					 ///Here we r converting the aakar to dari. if an aakar have space of its
					 ///before and after, then we r replace the aakar as dari

					 if ( i-1 < 0 )
						 break;

					 //making it Dari
					 if ( (charU[i-1]->Equals(space)) )//|| charU[i-1]->Equals((wchar_t)10))
					 {
						 charU[i] = dari;
					 }
					 break;
				 case newLine:
				if(charU[i]->Equals(newLine)){
					 //System::Windows::Forms::MessageBox::Show("new line");
					 i++;
					 break;
				 }
				 case rossoikar:
				  if(charU[i]->Equals(rossoikar) && i+1 < charU->Count){
					 // changing position of rossoikar with consonant
					if ( charU[i+1] )
						 {
							 wchar_t tmp = (wchar_t)charU[i+1];// copy the consonant
							 charU[i+1] = charU[i];
							 charU[i] = tmp;
							 i++;              
						 }
					 }
				 break;
				
				 case ekar:// 
					 ///If there is a ekar followed by aakar, then we are replace this both 
					 /// ookar
					 if (i+1 >= charU->Count)
						 break;
					 if (charU[i+1]->Equals(aakar))
					 {
						 charU->RemoveAt(i);
						 charU->RemoveAt(i);
						 charU->Insert(i,o_kar);
						 
					 }
					 break;
			//  o_kar =  2379; //ो 094B  
			//  ou_kar =  2380; //ौ 094C

				 case oikar://2376
					 if (i+1 >= charU->Count)
						 break;
					 if (charU[i+1]->Equals(aakar))
					 {
						 charU->RemoveAt(i);
						 charU->RemoveAt(i);
						 charU->Insert(i,ou_kar);
						 
					 }
					 
					 break;
				 case halanta:
					 if (i+1 >= charU->Count)
						 break;
					 if (charU[i+1]->Equals(aakar))
					 {
						 charU->RemoveAt(i);
						 charU->RemoveAt(i);
						 
					 }
					 
					 break;

				 };
				 
				 
			 }// end for

			 //cli::array<wchar_t,1>^ ch01 = charU->ToArray();
			 //System::Type^ t = charU[0]->GetType();
			 //System::Array^ aa = charU->ToArray(t);

			 len = charU->Count;
			 wchar_t *ch1 = new wchar_t[len];

			 for (int m = 0; m < len; m++)
				 ch1[m] = (wchar_t)charU[m];
			
			 ch1[len] = '\0';
			 System::String^ s = gcnew System::String(ch1);
			 return s;
		 }



 










 