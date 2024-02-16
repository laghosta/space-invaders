#include "Block.h"

Block::Block(Vector2 position) {
	this->position = position;
	size = { 3,3 };
	color = YELLOW;
}
Block::~Block() {

}

void Block::Draw() {
	DrawRectangleV(position, size, color);
}

Rectangle Block::GetRect()
{
	return { position.x, position.y, 3,3 };
}
