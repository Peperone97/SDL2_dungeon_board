#include "dropdownMenu.h"

DropdownMenu::DropdownMenu( int x, int y, int width, int height, SDL_Renderer *renderer ){
	texture = new Texture("img/sprites.png", renderer);
	arrowTexture = new Texture("img/sprites.png", renderer);
	activate = false;

	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;

	tile.x = 0;
	tile.y = 123;
	tile.w = 13;
	tile.h = 14;

	//the arrow for is 29% of total dropdown menu
	arrow_position.x = width - width*29/100;
	arrow_position.y = y;
	arrow_position.w = width*29/100+width*4/100;
	arrow_position.h = height;

	arrow_tile.x = 12;
	arrow_tile.y = 123;
	arrow_tile.w = 17;
	arrow_tile.h = 14;

	selection = new Phrase("", x+x*140/100, y+y*15/100, width, height*2, renderer);

}

void DropdownMenu::addEntry( const char* entry, SDL_Renderer *renderer ){
    n_entries++;
    if( n_entries == 1 ){
        entries = (Button**)malloc( sizeof(Button*) * n_entries );
    }else{
        entries = (Button**)realloc( entries, sizeof(Button*) * n_entries );
    }
	entries[n_entries-1] = new Button( entry, position.x, position.y+position.h*n_entries, position.w, position.h, renderer );
}

void DropdownMenu::handleEvent( int x, int y, enum Event e ){
	if( e == CLICK ){
		if( x >= arrow_position.x && x <= arrow_position.x + arrow_position.w ){
			if( y >= arrow_position.y && y <= arrow_position.y + arrow_position.h ){
				activate = !activate;
				if( activate ){
					arrowTexture->rotate(180);
				}else{
					arrowTexture->rotate(0);
				}
			}
		}else{
			for (int i = 0; i < n_entries; i++) {
				printf("Button: %i");
				if( entries[i]->isClicked( x, y ) ){
					setText( entries[i]->getText() );
				}
			}
			activate = false;
		}
	}else if( e == MOTION ){
		for (int i = 0; i < n_entries; i++) {
			entries[i]->isOnFocus( x, y );
		}
	}
}

void DropdownMenu::setText( const char *text ) {
	printf("%s\n", text);
	int l = selection->getPhraseLength();
	for( int i = 0; i < l; i++ ){
		selection->removeLastCharacter();
	}
	int i = 0;
	while( text[i] != '\0' ){
		selection->addCharacter( text[i] );
		i++;
	}
}

void DropdownMenu::render(SDL_Renderer* renderer) {
	texture->render(renderer, &tile, &position);
	arrowTexture->render(renderer, &arrow_tile, &arrow_position);
	selection->render(renderer);
	if(activate){
		for( int i = 0; i < n_entries; i++ ){
			entries[i]->render( renderer );
		}
	}
}

bool DropdownMenu::isActivate() {
	return activate;
}

DropdownMenu::~DropdownMenu(){
	delete selection;
	delete entries;
	delete texture;
}
