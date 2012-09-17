using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NOCR
{
    public class PostProcessor
    {
        private System.String processStr;
        private bool IsDependentVowel(char Vowel)
        {
            //Putting the values of the  unicode characters.
            //These values are defined by the unicode consortium
            //Unicode values are in Hexadecimal form.
            //We need to convert them into Decimal form before processing
            //For example Hex value of A (अ) is 0905 whereas the decimal value is 2309
            //We need to convert into windows xp alt keys before processing: so: converting Hex 0905 becomes 2309 in Decimal
            //const char aakar = 2494;

            const char aakar = (char)2366; //ा
            const char rossoikar = (char)2367; //ि 093F
            const char dirgikar = (char)2368; //ी 0940
            const char rossoUkar = (char)2369; //ु 0941
            const char dirgUkar = (char)2370; //ू 0942
            const char rrikar = (char)2371; // ृ 0943
            const char ekar = (char)2375; // े 0947
            const char oikar = (char)2376; //ै 0948
            const char o_kar = (char)2379; //ो 094B
            const char ou_kar = (char)2380; //ौ 094C
            const char newLine = (char)10;// \n A

            // const char oo = 2313;//उ 0909

            switch (Vowel)
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
        public PostProcessor()
        {

        }
        public PostProcessor(String textStr)
        {
            this.processStr = textStr;
            //Input text is textStr now assigned to the processStr
            //
        }
        public String TextPostProcessor()
        {
            int i;

            //this.processStr = this.processStr.Trim();
            //this step removes the extra spaces if present at the end of the text

            char[] ch = this.processStr.ToCharArray();
            int len = this.processStr.Length;

            List<char> charU = new List<char>();

            for (i = 0; i < len; i++)
                charU.Add(ch[i]);

            const char space = (char)32;// 

            const char bug = (char)39;// '
            const char Delete_del = (char)9676;//2492 it delete itself and also delete next to it

            const char aakar = (char)2366; //ा
            const char rossoikar = (char)2367; //ि 093F
            const char dirgikar = (char)2368; //ी 0940
            const char rossoUkar = (char)2369; //ु 0941
            const char dirgUkar = (char)2370; //ू 0942
            const char rrikar = (char)2371; // ृ 0943
            const char ekar = (char)2375; // े 0947
            const char oikar = (char)2376; //ै 0948
            const char o_kar = (char)2379; //ो 094B
            const char ou_kar = (char)2380; //ौ 094C

            const char chandrabindu = (char)2305; //ँ 0901
            const char a = (char)2309; //अ 0905
            const char Aa = (char)2310; //आ 0906			 

            const char halanta = (char)2381; //् 094D
            const char dari = (char)2404;
            const char oo = (char)2313;//उ 0909

            const char ga = (char)2327;// ग 0917


            const char za = (char)2479;
            const char onisar = (char)2434;
            const char newLine = (char)10;// \n A

            for (i = 0; i < charU.Count; i++)
            {


                if ((i + 1 < charU.Count) &&
                    this.IsDependentVowel((char)charU[i]) && this.IsDependentVowel((char)charU[i + 1]))
                {
                    // if there is any 2 Consecutive char is vowel 
                    //  and they are same then delete any one
                    if (charU[i].Equals(charU[i + 1]))
                    {
                        charU.RemoveAt(i);
                    }
                }

                if (charU[i].Equals(onisar)) // 2434
                {
                    // if a onisar come at the beganing of a word
                    // remove it
                    if (i - 1 < 0 || charU[i - 1].Equals(space))
                    {
                        charU.RemoveAt(i);
                        i--;
                    }
                }

                else if (charU[i].Equals(chandrabindu) && i + 1 < charU.Count)
                {
                    // changing position of chandrabindu with dependant vowel
                    // rule is : consonant + dependant vowel + chandrabindu
                    if (charU[i + 1].Equals(aakar))
                    {
                        char tmp = (char)charU[i + 1];// copy aakar
                        charU[i + 1] = charU[i];
                        charU[i] = tmp;
                    }
                }
                else if (charU[i].Equals(halanta))//2509
                {
                    // solving the problem of zofala
                    // zofala always sits befor dependent vowel
                    // here we r moving zofala before dependent vowel
                    if (i + 1 < charU.Count && charU[i + 1].Equals(za))
                    {
                        if ((i - 1 > 0) && this.IsDependentVowel((char)charU[i - 1]))
                        {
                            char tmp = (char)charU[i - 1];// copy dependent vowel
                            charU[i - 1] = charU[i];
                            charU[i] = charU[i + 1];
                            charU[i + 1] = tmp;
                        }
                    }// end zofala
                }//end of halanta				 
                else if (charU[i].Equals(bug))//39
                {
                    //just remove very small dot
                    charU.RemoveAt(i);
                    i--;

                }// end of bug
                else if (charU[i].Equals(Delete_del))//2492
                {
                    // it delete itself and also delete next to it
                    charU.RemoveAt(i);
                    if (this.IsDependentVowel((char)charU[i]))
                    {
                        charU.RemoveAt(i);
                    }
                    i--;
                }//end of delete

                //////////////////////////////////////////////////////////////////////////
                //////////////////////////////////////////////////////////////////////////
                //////////////////////////////////////////////////////////////////////////
                switch ((char)charU[i])
                {

                    case oo:
                        //If there is a ookar an a(oo), then we are replace this both 
                        // as a(Sori_O)
                        if (i + 1 >= charU.Count)
                            break;
                        if (charU[i + 1].Equals(aakar))
                        {

                            //	System.Windows.Forms.MessageBox.Show(charU[i+1].ToString(),charU[i].ToString());
                            charU.RemoveAt(i);
                            charU.RemoveAt(i);
                            charU.Insert(i, a);
                            //	 System.Windows.Forms.MessageBox.Show(charU[i].ToString(),a.ToString());

                            if (charU[i + 1].Equals(aakar))
                            {	 //if उ becomes अ then its possible that it might be आ so: 
                                charU.RemoveAt(i);
                                charU.RemoveAt(i);
                                charU.Insert(i, Aa);

                            }
                        }



                        break;
                    case a://2437
                        //If there is a aakar agter an a(Sori_O), then we are replace this both 
                        // as Aa(Sori_Aa)
                        if (i + 1 >= charU.Count)
                            break;
                        if (charU[i + 1].Equals(aakar))
                        {
                            charU.RemoveAt(i);
                            charU.RemoveAt(i);
                            charU.Insert(i, Aa);

                        }
                        break;

                    //case ga://2437
                    // ///If there is a aakar agter an a(Sori_O), then we are replace this both 
                    // /// as Aa(Sori_Aa)
                    // if (i+1 >= charU.Count)
                    //	 break;
                    // if (charU[i+1].Equals(halanta)&& charU[i+2].Equals(aakar))
                    // {
                    //	 charU.RemoveAt(i);
                    //	 charU.RemoveAt(i);
                    //	 charU.Insert(i,ga);
                    //	 
                    // }
                    // break;
                    case aakar://2494
                        //Here we r converting the aakar to dari. if an aakar have space of its
                        //before and after, then we r replace the aakar as dari

                        if (i - 1 < 0)
                            break;

                        //making it Dari
                        if ((charU[i - 1].Equals(space)))//|| charU[i-1].Equals((char)10))
                        {
                            charU[i] = dari;
                        }
                        break;
                    case newLine:
                        if (charU[i].Equals(newLine))
                        {
                            //System.Windows.Forms.MessageBox.Show("new line");
                            i++;
                            break;
                        }
                        break;
                    case rossoikar:
                        if (charU[i].Equals(rossoikar) && i + 1 < charU.Count)
                        {
                            // changing position of rossoikar with consonant
                            if (charU[i + 1] != null)
                            {
                                char tmp = (char)charU[i + 1];// copy the consonant
                                charU[i + 1] = charU[i];
                                charU[i] = tmp;
                                i++;
                            }
                        }
                        break;

                    case ekar:// 
                        //If there is a ekar followed by aakar, then we are replace this both 
                        // ookar
                        if (i + 1 >= charU.Count)
                            break;
                        if (charU[i + 1].Equals(aakar))
                        {
                            charU.RemoveAt(i);
                            charU.RemoveAt(i);
                            charU.Insert(i, o_kar);

                        }
                        break;
                    //  o_kar =  2379; //ो 094B  
                    //  ou_kar =  2380; //ौ 094C

                    case oikar://2376
                        if (i + 1 >= charU.Count)
                            break;
                        if (charU[i + 1].Equals(aakar))
                        {
                            charU.RemoveAt(i);
                            charU.RemoveAt(i);
                            charU.Insert(i, ou_kar);

                        }

                        break;
                    case halanta:
                        if (i + 1 >= charU.Count)
                            break;
                        if (charU[i + 1].Equals(aakar))
                        {
                            charU.RemoveAt(i);
                            charU.RemoveAt(i);

                        }

                        break;

                };


            }// end for

            //cli.array<char,1> ch01 = charU.ToArray();
            //System.Type t = charU[0].GetType();
            //System.Array aa = charU.ToArray(t);

            len = charU.Count;
            char[] ch1 = new char[len];

            for (int m = 0; m < len; m++)
                ch1[m] = (char)charU[m];

            //ch1[len] = '\0';
            System.String s = new System.String(ch1);
            return s;
        }
    }
}
