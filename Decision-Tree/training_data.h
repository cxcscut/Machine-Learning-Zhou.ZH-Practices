
#ifndef TRAINING_DATA_H
#define TRAINING_DATA_H

#include <string>

enum label { good, bad, NUM_OF_LABEL};
enum attr_type { color, root, sound, texture, navel, touch,NUM_OF_ATTR};
enum color {green,black,white,NUM_OF_COLOR};
enum root {curl,slightly_curl,straight,NUM_OF_ROOT};
enum sound {dull,very_dull,sharp,NUM_OF_SOUND};
enum texture {clear,slightly_blur,blur,NUM_OF_TEXTURE};
enum navel {hollow,slightly_hollow,flat,NUM_OF_NAVEL};
enum touch {smooth,sticky,NUM_OF_TOUCH};

struct attributes {
	int color, root, sound, texture, navel, touch;
	bool operator ==(const struct attributes &rhs) const
	{
		return (color == rhs.color) &&
			(root == rhs.root) &&
			(sound == rhs.sound) &&
			(texture == rhs.texture) &&
			(navel == rhs.navel) &&
			(touch == rhs.touch);
	}
};

struct training_data {
	struct attributes data_attr;
	int label;
};

typedef struct attributes attributes;
typedef struct training_data training_data;

#endif  // TRAINING_DATA_H