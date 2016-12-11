#include "generators.h"

#include <cstdlib>

std::string Generators::generate_name() {
  return random_element(first_names_) + " " + random_element(last_names_);
}

std::string Generators::generate_conference_name() {
  return random_element(conference_nouns_) + random_element(conference_endings_);
}

std::string Generators::generate_conference_email_subject(const std::string& conf_name) {
  std::string subject = random_element(conference_subjects_);
  replace_all(subject, "CONF", conf_name);
  return subject;
}

std::string Generators::generate_conference_email_body(const std::string& conf_name, const std::string& from, const std::string& month) {
  const int start = 10 + std::rand() % 13;
  const int end = start + std::rand() % 5;
  const int fee = (1 + std::rand() % 9) * 50;

  std::string body = random_element(email_greetings_) + "\n\n";
  body += random_element(conference_email_leaders_) + "\n\n";
  body += "  " + conf_name + "\n";

  body += "  " + month + " " + std::to_string(start);
  if (end > start) body += " - " + std::to_string(end);
  body += ", " + random_element(cities_) + "\n";

  body += "  Registration Fee: $" + std::to_string(fee) + "\n\n";
  body += random_element(email_signoffs_) + "\n" + from;

  replace_all(body, "CONF", conf_name);

  return body;
}

std::string Generators::random_element(std::vector<std::string> set) {
  // using modulo because lazy, don't really care about bias for now
  return set[std::rand() % set.size()];
}

void Generators::replace_all(std::string& string, const std::string& search, const std::string& replace) {
  size_t i = 0;
  while (true) {
    i = string.find(search, i);
    if (i == std::string::npos) break;

    string.replace(i, search.length(), replace);
    i += search.length();
  }
}

const std::vector<std::string> Generators::first_names_ = {
  "James", "John", "Robert", "Michael", "William", "David", "Richard",
  "Joseph", "Thomas", "Charles", "Christopher", "Daniel", "Matthew", "Anthony",
  "Donald", "Mark", "Paul", "Steven", "George", "Kenneth", "Andrew", "Joshua",
  "Edward", "Brian", "Kevin", "Ronald", "Timothy", "Jason", "Jeffrey", "Ryan",
  "Gary", "Jacob", "Nicholas", "Eric", "Stephen", "Jonathan", "Larry", "Scott",
  "Frank", "Justin", "Brandon", "Raymond", "Gregory", "Samuel", "Benjamin",
  "Patrick", "Jack", "Alexander", "Dennis", "Jerry", "Tyler", "Aaron", "Henry",
  "Douglas", "Peter", "Jose", "Adam", "Zachary", "Walter", "Nathan", "Harold",
  "Kyle", "Carl", "Arthur", "Gerald", "Roger", "Keith", "Jeremy", "Lawrence",
  "Terry", "Sean", "Albert", "Joe", "Christian", "Austin", "Willie", "Jesse",
  "Ethan", "Billy", "Bruce", "Bryan", "Ralph", "Roy", "Jordan", "Eugene",
  "Wayne", "Louis", "Dylan", "Alan", "Juan", "Noah", "Russell", "Harry",
  "Randy", "Philip", "Vincent", "Gabriel", "Bobby", "Johnny", "Howard",

  "Mary", "Patricia", "Jennifer", "Elizabeth", "Linda", "Barbara", "Susan",
  "Jessica", "Margaret", "Sarah", "Karen", "Nancy", "Betty", "Dorothy", "Lisa",
  "Sandra", "Ashley", "Kimberly", "Donna", "Carol", "Michelle", "Emily",
  "Helen", "Amanda", "Melissa", "Deborah", "Stephanie", "Laura", "Rebecca",
  "Sharon", "Cynthia", "Kathleen", "Shirley", "Amy", "Anna", "Angela", "Ruth",
  "Brenda", "Pamela", "Virginia", "Katherine", "Nicole", "Catherine",
  "Christine", "Samantha", "Debra", "Janet", "Carolyn", "Rachel", "Heather",
  "Maria", "Diane", "Emma", "Julie", "Joyce", "Frances", "Evelyn", "Joan",
  "Christina", "Kelly", "Martha", "Lauren", "Victoria", "Judith", "Cheryl",
  "Megan", "Alice", "Ann", "Jean", "Doris", "Andrea", "Marie", "Kathryn",
  "Jacqueline", "Gloria", "Teresa", "Hannah", "Sara", "Janice", "Julia",
  "Olivia", "Grace", "Rose", "Theresa", "Judy", "Beverly", "Denise", "Marilyn",
  "Amber", "Danielle", "Brittany", "Madison", "Diana", "Jane", "Lori",
  "Mildred", "Tiffany", "Natalie", "Abigail", "Kathy",
};

const std::vector<std::string> Generators::last_names_ = {
  "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller",
  "Wilson", "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White",
  "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson", "Clark",
  "Rodriguez", "Lewis", "Lee", "Walker", "Hall", "Allen", "Young", "Hernandez",
  "King", "Wright", "Lopez", "Hill", "Scott", "Green", "Adams", "Baker",
  "Gonzalez", "Nelson", "Carter", "Mitchell", "Perez", "Roberts", "Turner",
  "Phillips", "Campbell", "Parker", "Evans", "Edwards", "Collins", "Stewart",
  "Sanchez", "Morris", "Rogers", "Reed", "Cook", "Morgan", "Bell", "Murphy",
  "Bailey", "Rivera", "Cooper", "Richardson", "Cox", "Howard", "Ward",
  "Torres", "Peterson", "Gray", "Ramirez", "James", "Watson", "Brooks",
  "Kelly", "Sanders", "Price", "Bennett", "Wood", "Barnes", "Ross",
  "Henderson", "Coleman", "Jenkins", "Perry", "Powell", "Long", "Patterson",
  "Hughes", "Flores", "Washington", "Butler", "Simmons", "Foster", "Gonzales",
  "Bryant", "Alexander", "Russell", "Griffin", "Diaz", "Hayes", "Myers",
  "Ford", "Hamilton", "Graham", "Sullivan", "Wallace", "Woods", "Cole", "West",
  "Jordan", "Owens", "Reynolds", "Fisher", "Ellis", "Harrison", "Gibson",
  "McDonald", "Cruz", "Marshall", "Ortiz", "Gomez", "Murray", "Freeman",
  "Wells", "Webb", "Simpson", "Stevens", "Tucker", "Porter", "Hunter", "Hicks",
  "Crawford", "Henry", "Boyd", "Mason", "Morales", "Kennedy", "Warren",
  "Dixon", "Ramos", "Reyes", "Burns", "Gordon", "Shaw", "Holmes", "Rice",
  "Robertson", "Hunt", "Black", "Daniels", "Palmer", "Mills", "Nichols",
  "Grant", "Knight", "Ferguson", "Rose", "Stone", "Hawkins", "Dunn", "Perkins",
  "Hudson", "Spencer", "Gardner", "Stephens", "Payne", "Pierce", "Berry",
  "Matthews", "Arnold", "Wagner", "Willis", "Ray", "Watkins", "Olson",
  "Carroll", "Duncan", "Snyder", "Hart", "Cunningham", "Bradley", "Lane",
  "Andrews", "Ruiz", "Harper", "Fox", "Riley", "Armstrong", "Carpenter",
  "Weaver", "Greene", "Lawrence", "Elliott", "Chavez", "Sims", "Austin",
  "Peters", "Kelley", "Franklin", "Lawson", "Fields", "Gutierrez", "Ryan",
  "Schmidt", "Carr", "Vasquez", "Castillo", "Wheeler", "Chapman", "Oliver",
  "Montgomery", "Richards", "Williamson", "Johnston", "Banks", "Meyer",
  "Bishop", "McCoy", "Howell", "Alvarez", "Morrison", "Hansen", "Fernandez",
  "Garza", "Harvey", "Little", "Burton", "Stanley", "Nguyen", "George",
  "Jacobs", "Reid", "Kim", "Fuller", "Lynch", "Dean", "Gilbert", "Garrett",
  "Romero", "Welch", "Larson", "Frazier", "Burke", "Hanson", "Day", "Mendoza",
  "Moreno", "Bowman", "Medina", "Fowler", "Brewer", "Hoffman", "Carlson",
  "Silva", "Pearson", "Holland", "Douglas", "Fleming", "Jensen", "Vargas",
  "Byrd", "Davidson", "Hopkins", "May", "Terry", "Herrera", "Wade", "Soto",
  "Walters", "Curtis", "Neal", "Caldwell", "Lowe", "Jennings", "Barnett",
  "Graves", "Jimenez", "Horton", "Shelton", "Barrett", "O'brien", "Castro",
  "Sutton", "Gregory", "McKinney", "Lucas", "Miles", "Craig", "Rodriquez",
  "Chambers", "Holt", "Lambert", "Fletcher", "Watts", "Bates", "Hale",
  "Rhodes", "Pena", "Beck", "Newman", "Haynes", "McDaniel", "Mendez", "Bush",
  "Vaughn", "Parks", "Dawson", "Santiago", "Norris", "Hardy", "Love", "Steele",
  "Curry", "Powers", "Schultz", "Barker", "Guzman", "Page", "Munoz", "Ball",
  "Keller", "Chandler", "Weber", "Leonard", "Walsh", "Lyons", "Ramsey",
  "Wolfe", "Schneider", "Mullins", "Benson", "Sharp", "Bowen", "Daniel",
  "Barber", "Cummings", "Hines", "Baldwin", "Griffith", "Valdez", "Hubbard",
  "Salazar", "Reeves", "Warner", "Stevenson", "Burgess", "Santos", "Tate",
  "Cross", "Garner", "Mann", "Mack", "Moss", "Thornton", "Dennis", "McGee",
  "Farmer", "Delgado", "Aguilar", "Vega", "Glover", "Manning", "Cohen",
  "Harmon", "Rodgers", "Robbins", "Newton", "Todd", "Blair", "Higgins",
  "Ingram", "Reese", "Cannon", "Strickland", "Townsend", "Potter", "Goodwin",
  "Walton", "Rowe", "Hampton", "Ortega", "Patton", "Swanson", "Joseph",
  "Francis", "Goodman", "Maldonado", "Yates", "Becker", "Erickson", "Hodges",
  "Rios", "Conner", "Adkins", "Webster", "Norman", "Malone", "Hammond",
  "Flowers", "Cobb", "Moody", "Quinn", "Blake", "Maxwell", "Pope", "Floyd",
  "Osborne", "Paul", "McCarthy", "Guerrero", "Lindsey", "Estrada", "Sandoval",
  "Gibbs", "Tyler", "Gross", "Fitzgerald", "Stokes", "Doyle", "Sherman",
  "Saunders", "Wise", "Colon", "Gill", "Alvarado", "Greer", "Padilla", "Simon",
  "Waters", "Nunez", "Ballard", "Schwartz", "McBride", "Houston",
  "Christensen", "Klein", "Pratt", "Briggs", "Parsons", "McLaughlin",
  "Zimmerman", "French", "Buchanan", "Moran", "Copeland", "Roy", "Pittman",
  "Brady", "McCormick", "Holloway", "Brock", "Poole", "Frank", "Logan", "Owen",
  "Bass", "Marsh", "Drake", "Wong", "Jefferson", "Park", "Morton", "Abbott",
  "Sparks", "Patrick", "Norton", "Huff", "Clayton", "Massey", "Lloyd",
  "Figueroa", "Carson", "Bowers", "Roberson", "Barton", "Tran", "Lamb",
  "Harrington", "Casey", "Boone", "Cortez", "Clarke", "Mathis", "Singleton",
  "Wilkins", "Cain", "Bryan", "Underwood", "Hogan", "McKenzie", "Collier",
  "Luna", "Phelps", "McGuire", "Allison", "Bridges", "Wilkerson", "Nash",
  "Summers", "Atkins", "Wilcox", "Pitts", "Conley", "Marquez", "Burnett",
  "Richard", "Cochran", "Chase", "Davenport", "Hood", "Gates", "Clay", "Ayala",
  "Sawyer", "Roman", "Vazquez", "Dickerson", "Hodge", "Acosta", "Flynn",
  "Espinoza", "Nicholson", "Monroe", "Wolf", "Morrow", "Kirk", "Randall",
  "Anthony", "Whitaker", "O'connor", "Skinner", "Ware", "Molina", "Kirby",
  "Huffman", "Bradford", "Charles", "Gilmore", "Dominguez", "O'neal", "Bruce",
  "Lang", "Combs", "Kramer", "Heath", "Hancock", "Gallagher", "Gaines",
  "Shaffer", "Short", "Wiggins", "Mathews", "McClain", "Fischer", "Wall",
  "Small", "Melton", "Hensley", "Bond", "Dyer", "Cameron", "Grimes",
  "Contreras", "Christian", "Wyatt", "Baxter", "Snow", "Mosley", "Shepherd",
  "Larsen", "Hoover", "Beasley", "Glenn", "Petersen", "Whitehead", "Meyers",
  "Keith", "Garrison", "Vincent", "Shields", "Horn", "Savage", "Olsen",
  "Schroeder", "Hartman", "Woodard", "Mueller", "Kemp", "Deleon", "Booth",
  "Patel", "Calhoun", "Wiley", "Eaton", "Cline", "Navarro", "Harrell",
  "Lester", "Humphrey", "Parrish", "Duran", "Hutchinson", "Hess", "Dorsey",
  "Bullock", "Robles", "Beard", "Dalton", "Avila", "Vance", "Rich",
  "Blackwell", "York", "Johns", "Blankenship", "Trevino", "Salinas", "Campos",
  "Pruitt", "Moses", "Callahan", "Golden", "Montoya", "Hardin", "Guerra",
  "McDowell", "Carey", "Stafford", "Gallegos", "Henson", "Wilkinson", "Booker",
  "Merritt", "Miranda", "Atkinson", "Orr", "Decker", "Hobbs", "Preston",
  "Tanner", "Knox", "Pacheco", "Stephenson", "Glass", "Rojas", "Serrano",
  "Marks", "Hickman", "English", "Sweeney", "Strong", "Prince", "McClure",
  "Conway", "Walter", "Roth", "Maynard", "Farrell", "Lowery", "Hurst", "Nixon",
  "Weiss", "Trujillo", "Ellison", "Sloan", "Juarez", "Winters", "McLean",
  "Randolph", "Leon", "Boyer", "Villarreal", "McCall", "Gentry", "Carrillo",
  "Kent", "Ayers", "Lara", "Shannon", "Sexton", "Pace", "Hull", "Leblanc",
  "Browning", "Velasquez", "Leach", "Chang", "House", "Sellers", "Herring",
  "Noble", "Foley", "Bartlett", "Mercado", "Landry", "Durham", "Walls", "Barr",
  "McKee", "Bauer", "Rivers", "Everett", "Bradshaw", "Pugh", "Velez", "Rush",
  "Estes", "Dodson", "Morse", "Sheppard", "Weeks", "Camacho", "Bean", "Barron",
  "Livingston", "Middleton", "Spears", "Branch", "Blevins", "Chen", "Kerr",
  "McConnell", "Hatfield", "Harding", "Ashley", "Solis", "Herman", "Frost",
  "Giles", "Blackburn", "William", "Pennington", "Woodward", "Finley",
  "McIntosh", "Koch", "Best", "Solomon", "McCullough", "Dudley", "Nolan",
  "Blanchard", "Rivas", "Brennan", "Mejia", "Kane", "Benton", "Joyce",
  "Buckley", "Haley", "Valentine", "Maddox", "Russo", "McKnight", "Buck",
  "Moon", "McMillan", "Crosby", "Berg", "Dotson", "Mays", "Roach", "Church",
  "Chan", "Richmond", "Meadows", "Faulkner", "O'neill", "Knapp", "Kline",
  "Barry", "Ochoa", "Jacobson", "Gay", "Avery", "Hendricks", "Horne",
  "Shepard", "Hebert", "Cherry", "Cardenas", "McIntyre", "Whitney", "Waller",
  "Holman", "Donaldson", "Cantu", "Terrell", "Morin", "Gillespie", "Fuentes",
  "Tillman", "Sanford", "Bentley", "Peck", "Key", "Salas", "Rollins", "Gamble",
  "Dickson", "Battle", "Santana", "Cabrera", "Cervantes", "Howe", "Hinton",
  "Hurley", "Spence", "Zamora", "Yang", "McNeil", "Suarez", "Case", "Petty",
  "Gould", "McFarland", "Sampson", "Carver", "Bray", "Rosario", "Macdonald",
  "Stout", "Hester", "Melendez", "Dillon", "Farley", "Hopper", "Galloway",
  "Potts", "Bernard", "Joyner", "Stein", "Aguirre", "Osborn", "Mercer",
  "Bender", "Franco", "Rowland", "Sykes", "Benjamin", "Travis", "Pickett",
  "Crane", "Sears", "Mayo", "Dunlap", "Hayden", "Wilder", "McKay", "Coffey",
  "McCarty", "Ewing", "Cooley", "Vaughan", "Bonner", "Cotton", "Holder",
  "Stark", "Ferrell", "Cantrell", "Fulton", "Lynn", "Lott", "Calderon", "Rosa",
  "Pollard", "Hooper", "Burch", "Mullen", "Fry", "Riddle", "Levy", "David",
  "Duke", "O'donnell", "Guy", "Michael", "Britt", "Frederick", "Daugherty",
  "Berger", "Dillard", "Alston", "Jarvis", "Frye", "Riggs", "Chaney", "Odom",
  "Duffy", "Fitzpatrick", "Valenzuela", "Merrill", "Mayer", "Alford",
  "McPherson", "Acevedo", "Donovan", "Barrera", "Albert", "Cote", "Reilly",
  "Compton", "Raymond", "Mooney", "McGowan", "Craft", "Cleveland", "Clemons",
  "Wynn", "Nielsen", "Baird", "Stanton", "Snider", "Rosales", "Bright", "Witt",
  "Stuart", "Hays", "Holden", "Rutledge", "Kinney", "Clements", "Castaneda",
  "Slater", "Hahn", "Emerson", "Conrad", "Burks", "Delaney", "Pate",
  "Lancaster", "Sweet", "Justice", "Tyson", "Sharpe", "Whitfield", "Talley",
  "Macias", "Irwin", "Burris", "Ratliff", "McCray", "Madden", "Kaufman",
  "Beach", "Goff", "Cash", "Bolton", "McFadden", "Levine", "Good", "Byers",
  "Kirkland", "Kidd", "Workman", "Carney", "Dale", "McLeod", "Holcomb",
  "England", "Finch", "Head", "Burt", "Hendrix", "Sosa", "Haney", "Franks",
  "Sargent", "Nieves", "Downs", "Rasmussen", "Bird", "Hewitt", "Lindsay", "Le",
  "Foreman", "Valencia", "O'neil", "Delacruz", "Vinson", "Dejesus", "Hyde",
  "Forbes", "Gilliam", "Guthrie", "Wooten", "Huber", "Barlow", "Boyle",
  "McMahon", "Buckner", "Rocha", "Puckett", "Langley", "Knowles", "Cooke",
  "Velazquez", "Whitley", "Noel", "Vang",
};

const std::vector<std::string> Generators::cities_ = {
  "Seoul", "Sao Paulo", "Bombay", "Jakarta", "Karachi", "Moscow", "Istanbul",
  "Mexico City", "Shanghai", "Tokyo", "New York City", "Bangkok", "Beijing",
  "Delhi", "London", "Hong Kong", "Cairo", "Tehran", "Bogota", "Bandung",
  "Tianjin", "Lima", "Rio de Janeiro", "Lahore", "Bogor", "Santiago",
  "St Petersburg", "Shenyang", "Calcutta", "Wuhan", "Sydney", "Guangzhou",
  "Singapore", "Madras", "Baghdad", "Pusan", "Los Angeles", "Yokohama",
  "Dhaka", "Berlin", "Alexandria", "Bangalore", "Malang", "Hyderabad",
  "Chongqing", "Ho Chi Minh City", "Haerbin", "Ankara", "Buenos Aires",
  "Chengdu", "Ahmedabad", "Casablanca", "Chicago", "Xian", "Madrid",
  "Surabaya", "Pyongyang", "Nanjing", "Kinshasa", "Roma", "Taipei", "Osaka",
  "Kiev", "Yangon", "Toronto", "Zibo", "Dalian", "Taegu", "Addis Ababa",
  "Jinan", "Salvador", "Inchon", "Semarang", "Giza", "Changchun", "Havanna",
  "Nagoya", "Belo Horizonte", "Paris", "Tashkent", "Fortaleza", "Sukabumi",
  "Cali", "Guayaquil", "Qingdao", "Izmir", "Cirebon", "Taiyuan", "Brasilia",
  "Bucuresti", "Faisalabad", "Quezon City", "Medan", "Houston", "Abidjan",
  "Mashhad", "Medellín", "Kanpur", "Budapest", "Caracas",
};

const std::vector<std::string> Generators::conference_nouns_ = {
  "Talent", "Dream", "Publisher", "Cyber", "Web", "DevOps", "Design", "Tech",
  "Biz", "Ops", "Future", "App", "Developer", "Net", "Maker", "Hacker",
};

const std::vector<std::string> Generators::conference_endings_ = {
  "Force", "Con", " Summit", "Fest", " Symposium", " Consortium", " Faire",
};

const std::vector<std::string> Generators::conference_subjects_ = {
  "CONF",
  "CONF: You're Invited!",
  "Don't Miss CONF",
  "Register Now for CONF",
  "CONF Registration Now Open",
  "Are You Ready for CONF?",
};

const std::vector<std::string> Generators::conference_email_leaders_ = {
  // TODO write more leaders
  "  CONF is coming up very soon and registration is now open.  Please buy your\n"
  "tickets as soon as you can as we expect to sell out quickly.",
};

const std::vector<std::string> Generators::email_greetings_ = {
  "To Whom it May Concern:", "Dear sir or madam,", "Hi!",
};

const std::vector<std::string> Generators::email_signoffs_ = {
  "Best wishes,", "Sincerely,", "Hope to see you there,", "Regards,",
  "Thanks!",
};

