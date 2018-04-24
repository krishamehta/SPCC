import java.util.*;
import java.io.*;

class FF {
	static char ntermnl[], termnl[];
	static int ntlen, tlen;
	static String grmr[][], fst[], flw[];

	public static void main(String args[]) throws IOException {
		String nt, t;
		int i, j, n;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		// Input the list of non-terminals
		System.out.print("Enter the non-terminals: ");
		nt = br.readLine();
		ntlen = nt.length();
		ntermnl = new char[ntlen];
		ntermnl = nt.toCharArray();

		// Input the list of terminals
		System.out.print("Enter the terminals: ");
		t = br.readLine();
		tlen = t.length();
		termnl = new char[tlen];
		termnl = t.toCharArray();

		// Input the list of productions for each non-terminal
		System.out.println("Specify the grammar(Enter 9 for epsilon production)");
		grmr = new String[ntlen][];
		for (i = 0; i < ntlen; i++) {
			System.out.print("Enter the number of productions for " + ntermnl[i]+" : ");
			n = Integer.parseInt(br.readLine());
			grmr[i] = new String[n];
			System.out.print("Enter the productions: ");
			for (j = 0; j < n; j++)
				grmr[i][j] = br.readLine();
		}

		// Calculate and print first set 
		fst = new String[ntlen];
		for (i = 0; i < ntlen; i++)
			fst[i] = first(i);
		System.out.println("First Set");
		for (i = 0; i < ntlen; i++)
			System.out.println(ntermnl[i]+"\t"+removeDuplicates(fst[i]));
		
		// Calculate and print follow set 
		flw = new String[ntlen];
		for (i = 0; i < ntlen; i++)
			flw[i] = follow(i);
		System.out.println("Follow Set");
		for (i = 0; i < ntlen; i++)
			System.out.println(ntermnl[i]+"\t"+removeDuplicates(flw[i]));
	}

	static String first(int i) {
		int j, k, l = 0, isNT = 0;
		String temp = "", str = "";

		// Iterate over all the productions for the non-terminal
		for (j = 0; j < grmr[i].length; j++) {

			// Iterate over the characters of production
			for (k = 0; k < grmr[i][j].length(); k++, isNT = 0) {

				// Iterate over Non-Terminals and check if the character is one
				for (l = 0; l < ntlen; l++) {

					if (grmr[i][j].charAt(k) == ntermnl[l]) { 
						temp = first(l);
						
						if (!(temp.length() == 1 && temp.charAt(0) == '9'))
							str = str + temp;
						
						isNT = 1;
						break;
					}
				}

				// If it is an NT with epsilon in its FIRST then read next character of production
				if ( isNT == 1) {
					if (temp.contains("9"))
						continue;
				} 
				// Else it is a terminal
				else{
					str = str + grmr[i][j].charAt(k);
				}
				break;
			}
		}
		return str;
	}

	static String follow(int i) {
		int flag=0;
		char pro[], chr[];
		String temp = "";
		int j, k, l, m, n, found = 0;
		if (i == 0)
			temp = "$";

		// Iterate over all productions
		for (j = 0; j < ntlen; j++) {
			for (k = 0; k < grmr[j].length; k++) {

				pro = new char[grmr[j][k].length()];
				pro = grmr[j][k].toCharArray();

				// Iterate over the characters of production
				for (l = 0; l < pro.length; l++) {

					// Only If character is the Non-Terminal under consideration process it
					if (pro[l] == ntermnl[i]) { 

						// If it is the last position
						if (l == pro.length - 1) {

							// Follow of the parent NT if already calculated
							if (j < i)
								temp = temp + flw[j];
						}
						// If it is not the last character
						else {

							// Check with the NTs if the character is one
							for (m = 0; m < ntlen; m++) {
								if (pro[l + 1] == ntermnl[m]) { 
									chr = new char[fst[m].length()];
									chr = fst[m].toCharArray();
									for (n = 0; n < chr.length; n++) {
										flag=0;
										if (chr[n] == '9') { 
											if (l + 1 == pro.length - 1)
												temp = temp + follow(j); 
											else
											{
												flag = checkterminal(pro[l+2]);
												if(flag==1)
													temp=temp+pro[l+2];
												else
													temp=temp+first(pro[l+2]);
											}
										//temp = temp + follow(m);
										} else
										temp = temp + chr[n];
									}
									found = 1;
								}
							}
							if (found != 1)
								temp = temp + pro[l + 1];
						}
					}
				}
			}
		}
		return temp;
	}

	// Removes duplicates from the given string and returns the de-duplicated string
	static String removeDuplicates(String str) {
		int i;
		char ch;
		boolean seen[] = new boolean[256];
		String op = "";
		for (i = 0; i < str.length(); i++) {
			ch = str.charAt(i);
			if (!seen[ch]) {
				seen[ch] = true;
				op += ch;
			}
		}
		return op;
	}

	static int checkterminal(char ch) {
		int flag=0;
		for(int i=0;i<termnl.length;i++){
			if(termnl[i]==ch)
				flag=1;
		}	
		return flag;
	}

}

/*OUTPUT:

yash@yash-Inspiron-7560:~/Documents/College/SPCC$ javac FF.java
yash@yash-Inspiron-7560:~/Documents/College/SPCC$ java FF
Enter the non-terminals: ERTYF
Enter the terminals: ()+*i
Specify the grammar(Enter 9 for epsilon production)
Enter the number of productions for E : 1
Enter the productions: TR
Enter the number of productions for R : 2
Enter the productions: +TR
9
Enter the number of productions for T : 1
Enter the productions: FY
Enter the number of productions for Y : 2
Enter the productions: *FY
9
Enter the number of productions for F : 2
Enter the productions: (E)
i
First Set
E	(i
R	+9
T	(i
Y	*9
F	(i
Follow Set
E	$)
R	$)
T	+$)
Y	+$)
F	*+$)


*/
