
/*dynamic vector of unsigned chars*/
typedef struct vector
{
  unsigned char* data;
  size_t size; /*used size*/
  size_t allocsize; /*allocated size*/
} vector;

/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned vector_reserve(vector* p, size_t allocsize)
{
  if(allocsize > p->allocsize)
  {
    size_t newsize = (allocsize > p->allocsize * 2) ? allocsize : (allocsize * 3 / 2);
    void* data = realloc(p->data, newsize);
    if(data)
    {
      p->allocsize = newsize;
      p->data = (unsigned char*)data;
    }
    else return 0; /*error: not enough memory*/
  }
  return 1;
}

/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned vector_resize(vector* p, size_t size)
{
  if(!vector_reserve(p, size * sizeof(unsigned char))) return 0;
  p->size = size;
  return 1; /*success*/
}

static void vector_cleanup(void* p)
{
  ((vector*)p)->size = ((vector*)p)->allocsize = 0;
  free(((vector*)p)->data);
  ((vector*)p)->data = NULL;
}

static void vector_init(vector* p)
{
  p->data = NULL;
  p->size = p->allocsize = 0;
}

/*resize and give all new elements the value*/
static unsigned vector_resizev(vector* p, size_t size, unsigned char value)
{
  size_t oldsize = p->size, i;
  if(!vector_resize(p, size)) return 0;
  for(i = oldsize; i < size; i++) p->data[i] = value;
  return 1;
}

/*you can both convert from vector to buffer&size and vica versa. If you use
  init_buffer to take over a buffer and size, it is not needed to use cleanup*/
static void vector_init_buffer(vector* p, unsigned char* buffer, size_t size)
{
  p->data = buffer;
  p->allocsize = p->size = size;
}

/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned vector_push_back(vector* p, unsigned char c)
{
  if(!vector_resize(p, p->size + 1)) return 0;
  p->data[p->size - 1] = c;
  return 1;
}

