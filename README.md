Test Steps
----------

### Compile and Boot Device

获取学校列表

**Response**

```
[ 
  {
    "school_name": '',
    ...
  },
  {
    "school_name": '',
    ...
  }
]
```

Apartments List
---------------

### GET **/api/schools/:school_name/apartments?sort=&beds=&bath=...**

以学校为中心获取apartments列表

**Request**

| Parameter     | type   | validate | value           | Attribute | Default   | Note                                                               |
|:-------------:|:------:|:--------:|:---------------:|:---------:|:---------:|:------------------------------------------------------------------:|
|  school_name  | string | required |    columbia     |  unique   |           |                                                                    |
|     sort      | string |          | distance/rental |           | distance  |                             按什么排序                             |
|     beds      |  int   |          |    0/1/2/3/4    |           | 0返回全部 |                        只显示几张卧室的房间                        |
|     bath      |  int   |          |      0/1/2      |           | 0返回全部 |                        只返回bath个卫生间的                        |
|  price_lower  |  int   |          |     0-1500      |           |     0     |                         price lower bound                          |
|  price_upper  |  int   |          |                 | 500-2000  |   1500    |                         price upper bound                          |
| no_broker_fee |  bool  |          |   true/false    |           |   false   |                      false means "don't care"                      |
|  below_120th  |  bool  |          |   true/false    |           |   false   | false means don't care, it is a customised field only for Columbia |
|     page      |  int   |          |    1/2/3...     |           |     1     |                            page number                             |
|   per_page    |  int   |          |       10        |           |    10     |                           apts per page                            |
|    user_id    |  int   |          |                 |           |    -1     |   无效id也可以获取列表，只是会影响返回的对于房子是否wishlist的值   |

**Cautions**

**Response**

```json
[
  {
    "apt_id": 123456,
    "location_description": "136 W 109th ST",
    "location": TBD (for google map),
    "totoal_price": 3000,
    "beds": 2,
    "bath": 1,
    "cover_images": [
      "url1",
      "url2",
      ...
    ],
    "fans_avatars": [
      "url1",
      "url2",
      ...
    ],
    "distance": 0.3,
    "liked": true
  },
  {
  }
]
```

Apartment Detail
----------------

###GET **/api/apartments/:id**

根据apartment id返回房屋详细信息

**Request**

| Parameter | type | validate | value | Attribute |
|:---------:|:----:|:--------:|:-----:|:---------:|
|    id     | int  | required |       |  unique   |

**Response**

```json
{
  "total_price": 4000,
  "location": ,
  "description": "ssss",
  "elevator": true,
  "living_room": 2,
  "fans": [
    {
      "user_id": 123,
      "user_avatar": "url",
      "user_public_profile": "url",
      "user_roommate_requirements_summary": "不吸烟不喝酒",
    },
    {

    }
    ...
  ],
  "media": [
    "url1",
    "url2",
    ...
  ]
  "questions": [
    {
      "question": "xxxxxx",
      "answer": "xxxxxxx"
    },
    {

    }
  ]
}
```
